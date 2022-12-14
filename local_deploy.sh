#!/bin/sh 
readonly CWD="$(pwd)"
readonly BUILD_DIR=${CWD}"/build/"
readonly TARGET_IP="192.168.7.2"
readonly TARGET_PORT="3000"
readonly TARGET_DIR="/home/root/"
PROGRAM="ELE4205_PROJECT_"$1
PROGRAMPATH=${BUILD_DIR}/$1/

echo "Deploying to target"
echo ${PROGRAM}
echo ${PROGRAMPATH}
# Build
cmake --build ${BUILD_DIR} --target $PROGRAM

# kill all instance of the program on odroid 
ssh root@${TARGET_IP} "sh -c '/usr/bin/killall -q ${PROGRAM}; rm -rf ${TARGET_DIR}/${PROGRAM} ; exit 0'"

# send the program to the target
scp ${PROGRAMPATH}/${PROGRAM} root@${TARGET_IP}:${TARGET_DIR}

echo "Program on Server on Target"
#Activate driver on odroid 
ssh -t root@${TARGET_IP} "sh -c 'modprobe pwm-meson ;modprobe pwm-ctrl ; exit 0'"

# start server on target
ssh -t root@${TARGET_IP} "sh -c 'cd ${TARGET_DIR}; ./${PROGRAM}'"
