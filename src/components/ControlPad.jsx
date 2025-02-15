import { useContext } from "react";
import { BluetoothContext } from "./BlueToothProvider";

function ControlPad() {
    const {isConnected, move, isManualDrive,setIsManualDrive} = useContext(BluetoothContext);

    const handleMove = (direction) => {
        move(direction);
    }

    return(
        <div>
            <input type="checkbox" id="ManualDrive" name='ManualDrive' 
                    checked={isManualDrive}
                    onChange={(e) => setIsManualDrive(e.target.checked)}/>
            <label htmlFor="ManualDrive">{ isManualDrive? 'Disable Manual Drive' : 'Enable Manual Drive'}</label>
            <button disabled={!isConnected || isManualDrive} onClick={()=> handleMove('f')}>Forward</button>
            <button disabled={!isConnected || isManualDrive} onClick={()=> handleMove('b')}>Backward</button>
            <button disabled={!isConnected || isManualDrive} onClick={()=> handleMove('l')}>Left</button>
            <button disabled={!isConnected || isManualDrive} onClick={()=> handleMove('r')}>Right</button>
           
        </div>
    )
}

export default ControlPad;