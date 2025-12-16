import React from 'react';
import styles from './Ports.module.scss';
import { ATTU, Port } from '../../../model/dataModels';


interface PortsProps {
    selectedATTU?: ATTU;
    ports?: Port[],
    setSelectedPort: (port: Port) => void 
}

const Ports: React.FC<PortsProps> = ({selectedATTU,  ports, setSelectedPort }) => {


    return (
        <div className={styles.portsContainer}>
            <h3>ATTU Ports - {selectedATTU?.attuIp}</h3>
            <p>Select a port: </p>
            <div className={styles.portsGrid}>
                {ports?.map((p) => (
                    <button onClick={() => setSelectedPort(p)} key={p.id} className={styles.portButton}>
                        {p.portNumber}
                    </button>
                ))}
            </div>
        </div>
    )
};

export default Ports;
