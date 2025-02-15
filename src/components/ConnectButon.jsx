import { useContext } from "react";
import { BluetoothContext } from "./BlueToothProvider";

function ConnectButton(){
    const {isConnected, connectBluetooth,disconnectBluetooth} = useContext(BluetoothContext);
    const handleConnect = async () =>{
        if(!isConnected){
            connectBluetooth();
        }else{
            disconnectBluetooth();
        }
    };

    return(
        <button onClick={handleConnect}>
            {isConnected ? 'Desconectar' : 'Conectar'}
        </button>
    );
};

export default ConnectButton;