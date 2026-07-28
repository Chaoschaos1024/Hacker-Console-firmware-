#!/bin/bash
# Hacker Console 树莓派服务安装脚本

set -e  # 遇到错误立即退出

# 颜色定义
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo -e "${GREEN}>>> 开始安装 Hacker Console 服务...${NC}"

# 1. 检查是否为树莓派
if ! grep -q "Raspberry Pi" /proc/device-tree/model 2>/dev/null; then
    echo -e "${YELLOW}警告: 未检测到树莓派，脚本可能在其他系统上无法正常工作。${NC}"
fi

# 2. 更新系统并安装依赖
echo -e "${GREEN}>>> 更新系统并安装 Python 依赖...${NC}"
sudo apt update
sudo apt install -y python3-pip python3-serial python3-psutil

# 3. 创建脚本存放目录并复制文件
echo -e "${GREEN}>>> 部署 Python 脚本...${NC}"
SERVICE_DIR="/usr/local/bin"
sudo mkdir -p "$SERVICE_DIR"

# 关键步骤：假设你的 Python 脚本名为 hacker_console_sender.py，并和 install.sh 在同一目录
# 你也可以从 GitHub 上的其他路径复制，这里需要你根据实际情况修改来源路径
SOURCE_SCRIPT="hacker_console_sender.py" 
if [ -f "$SOURCE_SCRIPT" ]; then
    sudo cp "$SOURCE_SCRIPT" "$SERVICE_DIR/"
    sudo chmod +x "$SERVICE_DIR/hacker_console_sender.py"
    echo -e "${GREEN}>>> 脚本已部署至 $SERVICE_DIR${NC}"
else
    echo -e "${RED}错误: 找不到源脚本 $SOURCE_SCRIPT，请检查文件路径。${NC}"
    exit 1
fi

# 4. 创建 systemd 服务文件
echo -e "${GREEN}>>> 安装 systemd 服务...${NC}"
SERVICE_FILE="/etc/systemd/system/hacker-console.service"
sudo tee "$SERVICE_FILE" > /dev/null <<EOF
[Unit]
Description=Hacker Console Data Sender
After=network.target multi-user.target

[Service]
Type=simple
ExecStart=/usr/bin/python3 $SERVICE_DIR/hacker_console_sender.py
Restart=always
RestartSec=10
StandardOutput=append:/var/log/hacker_console.log
StandardError=append:/var/log/hacker_console_error.log
User=root

[Install]
WantedBy=multi-user.target
EOF

# 5. 重载 systemd 并启用服务
echo -e "${GREEN}>>> 启动并启用服务...${NC}"
sudo systemctl daemon-reload
sudo systemctl enable hacker-console.service
sudo systemctl restart hacker-console.service

# 6. 查看服务状态
echo -e "${GREEN}>>> 服务状态:${NC}"
sudo systemctl status hacker-console.service --no-pager

echo -e "${GREEN}>>> 安装完成！${NC}"
echo "你可以使用以下命令管理服务："
echo "  启动: sudo systemctl start hacker-console"
echo "  停止: sudo systemctl stop hacker-console"
echo "  查看日志: sudo journalctl -u hacker-console -f"