import { useEffect, useContext } from "react";
import { BluetoothContext } from "../components/BlueToothProvider";

const useKeyPress = () => {
    const { isManualDrive, writeCharacteristicRef } = useContext(BluetoothContext);
  
    useEffect(() => {
        const encoder = new TextEncoder();
        const handleKeyPress = async (e) => {
            if (!isManualDrive || !writeCharacteristicRef?.current) return;
            if (e.repeat) return; 
            // Ejemplo: Enviar comandos según tecla presionada
            switch(e.key.toLowerCase()) {
                case 'w':
                    await writeCharacteristicRef.current.writeValue(encoder.encode('w\n'));
                    // console.log("w");
                    break;
                case 's':
                    await writeCharacteristicRef.current.writeValue(encoder.encode('s\n'));
                    // console.log("s");
                    break;
                case 'a':
                    await writeCharacteristicRef.current.writeValue(encoder.encode('a\n'));
                    // console.log("a");
                    break;
                case 'd':
                    await writeCharacteristicRef.current.writeValue(encoder.encode('d\n'));
                    // console.log("d");
                    break;
            }
        };
  
        const handleKeyUp = async () => {
            if (!isManualDrive || !writeCharacteristicRef?.current) return;
            await writeCharacteristicRef.current.writeValue(encoder.encode('p\n'));
        }
        window.addEventListener('keydown', handleKeyPress);
        window.addEventListener('keyup',handleKeyUp);
        return () => {
            window.removeEventListener('keydown', handleKeyPress);
            window.removeEventListener('keyup', handleKeyUp)
        };
    }, [isManualDrive, writeCharacteristicRef]); // Dependencias cruciales
  };
  
  export default useKeyPress;