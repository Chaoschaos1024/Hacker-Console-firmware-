#!/usr/bin/env python3
"""
Hacker Console 数据发送服务
向 USB CDC ACM 设备发送系统状态数据
"""

import serial
import time
import psutil
import os
import sys
import glob
import logging
from datetime import datetime

# 配置日志
LOG_FILE = "/var/log/hacker_console.log"
logging.basicConfig(
    level=logging.INFO,
    format='%(asctime)s - %(levelname)s - %(message)s',
    handlers=[
        logging.FileHandler(LOG_FILE),
        logging.StreamHandler()
    ]
)

# 设备VID/PID
VID = 0xBEEF
PID = 0xCAFE

class HackerConsoleSender:
    def __init__(self):
        self.serial_port = None
        self.device_path = None
        
    def find_device(self):
        """查找并返回设备路径"""
        # 在 /dev 下查找 ttyACM* 或 ttyUSB* 设备
        patterns = ['/dev/ttyACM*', '/dev/ttyUSB*']
        
        for pattern in patterns:
            devices = glob.glob(pattern)
            for dev in devices:
                try:
                    # 尝试读取设备的udev信息
                    import subprocess
                    cmd = f"udevadm info --query=property --name={dev} | grep -E 'ID_VENDOR_ID|ID_MODEL_ID'"
                    result = subprocess.run(cmd, shell=True, capture_output=True, text=True)
                    
                    if result.returncode == 0:
                        output = result.stdout
                        if f"ID_VENDOR_ID={VID:04x}" in output and f"ID_MODEL_ID={PID:04x}" in output:
                            logging.info(f"找到设备: {dev}")
                            return dev
                except Exception as e:
                    logging.debug(f"检查 {dev} 时出错: {e}")
                    continue
        return None
    
    def connect(self):
        """连接设备"""
        self.device_path = self.find_device()
        if not self.device_path:
            logging.error("未找到 Hacker Console 设备!")
            return False
        
        try:
            self.serial_port = serial.Serial(
                port=self.device_path,
                baudrate=115200,  # 根据你的Pico设置调整
                bytesize=serial.EIGHTBITS,
                parity=serial.PARITY_NONE,
                stopbits=serial.STOPBITS_ONE,
                timeout=1
            )
            logging.info(f"成功连接到 {self.device_path}")
            return True
        except Exception as e:
            logging.error(f"连接失败: {e}")
            return False
    
    def map_value(self, value, in_min=0, in_max=100, out_min=0, out_max=31):
        """将0-100的值映射到0-31"""
        # 确保值在范围内
        value = max(in_min, min(in_max, value))
        return int((value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min)
    
    def get_system_stats(self):
        """获取系统状态"""
        try:
            # CPU使用率 (0-100)
            cpu_percent = psutil.cpu_percent(interval=0.5)
            
            # CPU温度 (Raspberry Pi)
            temp = 0
            try:
                with open('/sys/class/thermal/thermal_zone0/temp', 'r') as f:
                    temp = float(f.read().strip()) / 1000.0
                # 映射温度: 30-80°C -> 0-31
                temp_mapped = self.map_value(int(temp), 30, 80)
            except:
                temp_mapped = 0
            
            # 内存使用率
            ram = psutil.virtual_memory().percent
            
            # 磁盘使用率
            disk = psutil.disk_usage('/').percent
            
            # 网络使用率 (简单示例，需要更复杂的计算)
            net = 0
            
            # Linux发行版识别
            distro = self.get_distro()
            
            return {
                'cpu': self.map_value(int(cpu_percent)),
                'temp': temp_mapped,
                'ram': self.map_value(int(ram)),
                'disk': self.map_value(int(disk)),
                'net': self.map_value(int(net)),
                'distro': distro
            }
        except Exception as e:
            logging.error(f"获取系统状态失败: {e}")
            return None
    
    def get_distro(self):
        """识别Linux发行版"""
        try:
            with open('/etc/os-release', 'r') as f:
                content = f.read()
                if 'ubuntu' in content.lower():
                    return 0x01
                elif 'debian' in content.lower():
                    return 0x02
                elif 'rhel' in content.lower() or 'red hat' in content.lower():
                    return 0x03
                elif 'fedora' in content.lower():
                    return 0x04
                elif 'arch' in content.lower():
                    return 0x05
                elif 'mint' in content.lower():
                    return 0x06
                elif 'opensuse' in content.lower():
                    return 0x07
                elif 'centos' in content.lower():
                    return 0x08
                elif 'kali' in content.lower():
                    return 0x09
                elif 'raspbian' in content.lower() or 'raspberry' in content.lower():
                    return 0x0A
        except:
            pass
        return 0x00
    
    def create_packet(self, stats):
        """创建数据包
        格式: 0xAA + 6字节数据 + 校验和 + 0xBB
        数据: cpu(5bit) + temp(5bit) + ram(5bit) + disk(5bit) + net(5bit) + distro(5bit)
        """
        # 确保每个值都在0-31范围内
        cpu = stats['cpu'] & 0x1F
        temp = stats['temp'] & 0x1F
        ram = stats['ram'] & 0x1F
        disk = stats['disk'] & 0x1F
        net = stats['net'] & 0x1F
        distro = stats['distro'] & 0x1F
        
        # 计算校验和 (异或)
        checksum = cpu ^ temp ^ ram ^ disk ^ net ^ distro
        
        # 构建数据包
        packet = bytes([
            0xAA,           # 帧头
            cpu,
            temp,
            ram,
            disk,
            net,
            distro,
            checksum,       # 校验和
            0xBB            # 帧尾
        ])
        
        return packet
    
    def send_data(self):
        """发送数据"""
        stats = self.get_system_stats()
        if not stats:
            return False
        
        packet = self.create_packet(stats)
        
        try:
            if self.serial_port and self.serial_port.is_open:
                self.serial_port.write(packet)
                logging.debug(f"发送数据: CPU={stats['cpu']}, Temp={stats['temp']}, RAM={stats['ram']}")
                return True
            else:
                logging.warning("串口未打开，尝试重新连接")
                return False
        except Exception as e:
            logging.error(f"发送失败: {e}")
            return False
    
    def run(self, interval=1.0):
        """主循环"""
        logging.info("Hacker Console 数据发送服务启动")
        
        if not self.connect():
            logging.error("初始连接失败，将在循环中重试")
        
        while True:
            try:
                # 如果连接断开，尝试重新连接
                if not self.serial_port or not self.serial_port.is_open:
                    logging.warning("连接断开，尝试重新连接...")
                    self.connect()
                    time.sleep(2)
                    continue
                
                # 发送数据
                if not self.send_data():
                    # 发送失败，标记连接可能已断开
                    self.serial_port = None
                
                # 等待下一次发送
                time.sleep(interval)
                
            except KeyboardInterrupt:
                logging.info("收到中断信号，正在退出...")
                break
            except Exception as e:
                logging.error(f"运行错误: {e}")
                time.sleep(5)
        
        if self.serial_port and self.serial_port.is_open:
            self.serial_port.close()
        logging.info("服务已停止")

def main():
    sender = HackerConsoleSender()
    
    # 检查必要的Python库
    try:
        import psutil
    except ImportError:
        print("错误: 需要安装 psutil 库")
        print("请运行: sudo pip3 install psutil")
        sys.exit(1)
    
    sender.run()

if __name__ == "__main__":
    main()