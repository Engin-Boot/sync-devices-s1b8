# Synchronize Devices

## General Procedure | Asynchronous MQTT

1. Create a client object
2. Set the options to connect to an MQTT server
3. Set up callback functions
4. Connect the client to an MQTT server
5. Subscribe to any topic the client needs to receive
6. Repeat until finished:
    - Publish any messages the client needs to
    - Handle any incoming messages
7. Disconnect the client
8. Free any memory being used by the client

## Asynchronous MQTT for Data synchronization between devices

### Prerequisites

    - git clone https://github.com/eclipse/paho.mqtt.c.git
    - cd paho.mqtt.c
    - make -j
    - sudo make install
    -pip3 install quick-mailer

### Build

```./build_all_devices.sh```

creates a folder 'bin' and pupulates it with all the client executables

### Clean Build

```./clean_build.sh```

### Run

Run all three console applications in different terminals.

### Build and Run Python Client

```python3 MRI_Client.py```

#### Options

1. Add a new patient.
2. Edit current patient data.
3. View current Patient data.
4. View Total Count Of Patients.
5. Exit.

### Synchronization

- Adding a new patient in any of the clients will automatically add the patient in all the clients.
- Editing patient data in any of the clients will automatically reflect changes in all the clients.
