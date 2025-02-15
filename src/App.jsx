import './App.css'
import ConnectButton from './components/ConnectButon';
import ControlPad from './components/ControlPad';

import ParmsForm from './components/ParmsForm';
import useKeyPress from './hooks/useKeyPress';



function App() {
  useKeyPress();
  return (
      <main className='App'>
        <h1>Bluetooth Control</h1>
        <ConnectButton />
        <ControlPad/>
        <ParmsForm/>
      </main>
  )
}

export default App
