import { useContext, useState } from "react";
import { BluetoothContext } from './BlueToothProvider';

function ParmsForm(){
    const {setParams, isConnected} = useContext(BluetoothContext);
    const [speed, setSpeed] = useState(1);
    const [distance, setDistance] = useState(0.3);
    const [angle, setAngle] = useState(90);

    const handleSubmit = (event) => {
        event.preventDefault();
        setParams({speed, distance,angle})
    };

    return(
        <>
        {
            isConnected?
            <form onSubmit={handleSubmit}>
                <h2>Set distance (meters)</h2>
                <input 
                    type="number" 
                    name="distance" 
                    min='0'
                    step="0.1"
                    value={distance}
                    onChange={(e) => {setDistance(e.target.value)}}
                    required
                />

                <h2>Set speed (between 0 and 9)</h2>
                <input 
                    type="number" 
                    name="speed" 
                    min='0'
                    max='9' 
                    value={speed}
                    onChange={(e) => {setSpeed(e.target.value)}}
                    required
                />

                <h2>Set Angle (between 0 and 360)</h2>
                <input 
                    type="number" 
                    name="speed" 
                    min='0'
                    max='360' 
                    value={angle}
                    onChange={(e) => {setAngle(e.target.value)}}
                    required
                />
                <button type="submit">Apply</button>
            </form>
            :''
        }
        </>
    )
}

export default ParmsForm;