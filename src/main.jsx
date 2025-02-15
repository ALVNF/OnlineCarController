import { BluetoothProvider } from './components/BlueToothProvider';
import { createRoot } from 'react-dom/client'
import './index.css'
import App from './App.jsx'

createRoot(document.getElementById('root')).render(
  <BluetoothProvider>
    <App />
  </BluetoothProvider>,
)
