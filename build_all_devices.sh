mkdir bin

# CT
g++ DEVICES/CT/*.cpp Patient/*.cpp -o ./bin/CT_CLIENT -lpaho-mqtt3as

# ULTRASOUND
g++ DEVICES/ULTRASOUND/*.cpp Patient/*.cpp -o ./bin/ULTRASOUND_CLIENT -lpaho-mqtt3as

# ECG
g++ DEVICES/ECG/*.cpp Patient/*.cpp -o ./bin/ECG_CLIENT -lpaho-mqtt3as