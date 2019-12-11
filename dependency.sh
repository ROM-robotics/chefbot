
sudo apt install g++ gcc git pytyon3-dev python3-pip python3-setuptools vim
sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
sudo apt-key adv --keyserver 'hkp://keyserver.ubuntu.com:80' --recv-key C1CF6E31E6BADE8868B172B4F42ED6FBAB17C654
sudo apt-get update
sudo apt-get install ros-kinetic-ros-base
sudo rosdep init
rosdep update
echo "source /opt/ros/kinetic/setup.bash" >> ~/.bashrc
sudo apt install python-rosinstall python-rosinstall-generator python-wstool build-essential





////////
ros package 

chefbot
sudo apt install ros-kinetic-urdf
sudo apt install ros-kinetic-map-server
sudo apt install ros-kinetic-tf
sudo apt install ros-kinetic-move-base-msgs ros-kinetic-move-base
sudo apt install ros-kinetic-xacro
sudo apt install ros-kinetic-salm-gmapping ros-kinetic-amcl ros-kinetic-dwa-local-planner
sudo apt install ros-kinetic-rplidar-ros
sudo apt install ros-kinetic-rosserial-python ros-kinetic-rosserial-arduino
sudo apt install ros-kinetic-tf2-geometry-msgs

git clone --branch pi3-devel https://github.com/greenghostman/chefbot

