import { createContext, useEffect, useRef, useState } from "react";

const BluetoothContext = createContext();

const PRIMARY_SERVICE_UUID = '0000ffe0-0000-1000-8000-00805f9b34fb';
const WRITE_CHARACTERISTIC_UUID = '0000ffe2-0000-1000-8000-00805f9b34fb';
const NOTIFICATION_CHARACTERISTIC_UUID  = '0000ffe1-0000-1000-8000-00805f9b34fb';


const BluetoothProvider = ({children}) => {
    const [device, setDevice] = useState(null);
    const [writeCharacteristic, setWriteCharacteristic] = useState(null);
    const writeCharacteristicRef = useRef(null); // Inicialmente null
    const [notificationCharacteristic, setNotificationCharacteristic]  = useState(false);
    const [isConnected, setIsConnected] = useState(false);
    const [isManualDrive, setIsManualDrive] = useState(false);

    const connectBluetooth = async() =>{
        try {
            const device = await navigator.bluetooth.requestDevice({
                acceptAllDevices: true,
                optionalServices: [PRIMARY_SERVICE_UUID],
            });

            const server = await device.gatt.connect();
            const service = await server.getPrimaryService(PRIMARY_SERVICE_UUID);
            const writeChar = await service.getCharacteristic(WRITE_CHARACTERISTIC_UUID);
            const notiChar = await service.getCharacteristic(NOTIFICATION_CHARACTERISTIC_UUID);

            setDevice(device);
            setIsConnected(true);
            setWriteCharacteristic(writeChar);
            setNotificationCharacteristic(notiChar);

        } catch (error) {
            console.error("Connection Error:",error);
        }
    }

    const disconnectBluetooth = () => {
        if (device && device.gatt.connected) {
            device.gatt.disconnect();
            setIsConnected(false);
            setDevice(null);
            setNotificationCharacteristic(null);
            setWriteCharacteristic(null)

        }
    }

    useEffect(() => {
        if (writeCharacteristic) {
            writeCharacteristicRef.current = writeCharacteristic; // Se inicializa cuando writeCharacteristic cambia
        }
    }, [writeCharacteristic]); // Se ejecuta solo cuando writeCharacteristic cambia

    useEffect(() => {
        if(!notificationCharacteristic) return;

        const handleNotification = (event) =>{
            const value = new  TextDecoder().decode(event.target.value);
            console.log("Received:",value);   
        }

        notificationCharacteristic.startNotifications()
        .then(() => {
            notificationCharacteristic.addEventListener("characteristicvaluechanged", handleNotification);
        })
        .catch(error => console.error("Error enabling notifications:",error));

        return () => {
            // notificationCharacteristic.stopNotifications().catch(console.error);
            notificationCharacteristic.removeEventListener("characteristicvaluechanged", handleNotification);
        }

    },[notificationCharacteristic])

    // En tu componente:
    useEffect(() => {
        const handleModeChange = async () => {
        try {
            if(writeCharacteristicRef.current == null) return;
            const encoder = new TextEncoder();
            if (isManualDrive) {
                console.log("Modo manual activado");
                await writeCharacteristicRef.current.writeValueWithoutResponse(encoder.encode("MODE1"));
            } else {
                console.log("Modo automático activado");
                await writeCharacteristicRef.current.writeValueWithoutResponse(encoder.encode("MODE0"));
            }
        } catch (error) {
            console.error("Error:", error);
        }
        };
    
        handleModeChange();
    }, [isManualDrive]);


    const move = async (direction) =>{
        if(!device || !device.gatt.connected) return;

        try {
            const encoder = new TextEncoder();
            await writeCharacteristic.writeValueWithoutResponse(encoder.encode(direction));
            console.log("Command sent: ", direction);
            
        } catch (error) {
            console.error("Error while trying to move:", error);
        }
    }

    const setParams = async ({speed, distance,angle}) =>{
        if(!device || !device.gatt.connected) return;

        try {
            const dataString = `${Number(distance).toFixed(2)} ${Number(speed)} ${Number(angle)}` + '\r\n'; // Añadir \r\n
            const encoder = new TextEncoder();
            await writeCharacteristic.writeValueWithoutResponse(encoder.encode(dataString));
            console.log("Command sent:", dataString.trim());
            
        } catch (error) {
            console.error("Error while trying to move:", error);
        }
    }

    return (
        <BluetoothContext.Provider value={{isConnected, connectBluetooth, disconnectBluetooth, move, setParams, isManualDrive,setIsManualDrive,writeCharacteristicRef}}>
            {children}
        </BluetoothContext.Provider>
    );
};

export {BluetoothContext, BluetoothProvider};