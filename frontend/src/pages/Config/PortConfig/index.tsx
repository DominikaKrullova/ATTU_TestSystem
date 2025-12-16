import React, { useState } from 'react'
import styles from './PortConfig.module.scss'
import { RootState } from '../../../store/store';
import { useDispatch, useSelector } from 'react-redux';
import { updatePort } from '../../../store/slices/attuSlice';
import classNames from 'classnames';
import { ATTU, Port } from '../../../model/dataModels';

interface PortConfigProps {
    attu?: ATTU,
    port?: Port,
    onClose: () => void;
}


const PortConfig: React.FC<PortConfigProps> = ({ attu, port, onClose }) => {

    const dispatch = useDispatch();
    const [name, setName] = useState<string>(port?.portConfig.name || '');
    const [baudRate, setBaudRate] = useState<number>(port?.portConfig.baudRate || 9600);
    const [parity, setParity] = useState<string>(port?.portConfig.parity || 'none');
    const [flowControl, setFlowControl] = useState<boolean>(port?.portConfig.flowControl || false);
    const [dataBits, setDataBits] = useState<number>(port?.portConfig.dataBits || 8);
    const [stopBits, setStopBits] = useState<number>(port?.portConfig.stopBits || 1);
    const [protocol, setProtocol] = useState<string>(port?.portConfig.protocol || 'ASCII');

    const handleSave = () => {
        if (!attu || !port) return;
        dispatch(
            updatePort({
                attuIp: attu.attuIp,
                port: {
                    id: port.id,
                    portNumber: port.portNumber,
                    portConfig: {
                        name,
                        baudRate,
                        parity,
                        flowControl,
                        dataBits,
                        stopBits,
                        protocol,
                    },
                },
            })
        );
        onClose();
    };

    if (!port || !attu) return null;


    return (
        <div className={styles.configModal}>
            <div className={styles.attuInfo}>
                <span>{attu.attuIp}</span>
                <span>Port: {port.portNumber}</span>
            </div>
            <section className={styles.configContainer}>
                <div className={styles.formItem}>
                    <label>Name</label>
                    <input
                        className={styles.input}
                        value={name}
                        onChange={(e) => setName(e.target.value)}
                    />
                </div>
                <div className={styles.formItem}>
                    <label>Baud Rate</label>
                    <select
                        className={styles.select}
                        value={baudRate}
                        onChange={(e) => setBaudRate(Number(e.target.value))}
                    >
                        <option value="9600">9600</option>
                        <option value="19200">19200</option>
                        <option value="115200">115200</option>
                    </select>
                </div>
                <div className={styles.formItem}>
                    <label>Parity</label>
                    <div className={styles.buttons}>
                        {['none', 'odd', 'even'].map((option) => (
                            <button
                                key={option}
                                className={classNames({ [styles.selected]: parity === option })}
                                onClick={() => setParity(option)}
                            >
                                {option}
                            </button>
                        ))}
                    </div>
                </div>
                <div className={styles.formItem}>
                    <label>Flow Control</label>
                    <button
                        className={classNames({ [styles.selected]: flowControl })}
                        onClick={() => setFlowControl(!flowControl)}
                    >
                        {flowControl ? 'Enabled' : 'Disabled'}
                    </button>
                </div>
                <div className={styles.formItem}>
                    <label>Data Bits</label>
                    <div className={styles.buttons}>
                        {[5, 6, 7, 8].map((bits) => (
                            <button
                                key={bits}
                                className={classNames({ [styles.selected]: dataBits === bits })}
                                onClick={() => setDataBits(bits)}
                            >
                                {bits}
                            </button>
                        ))}
                    </div>
                </div>
                <div className={styles.formItem}>
                    <label>Stop Bits</label>
                    <div className={classNames(styles.buttons, styles.stopBitsButtons)}>
                        {[1, 2].map((bit) => (
                            <button
                                key={bit}
                                className={classNames(styles.button, { [styles.selected]: stopBits === bit })}
                                onClick={() => setStopBits(bit)}
                            >
                                {bit}
                            </button>
                        ))}
                    </div>
                </div>
                <div className={styles.formItem}>
                    <label>Protocol</label>
                    <select
                        className={styles.select}
                        value={protocol}
                        onChange={(e) => setProtocol(e.target.value)}
                    >
                        <option>ASCII</option>
                        <option>EM3000</option>
                        <option>RDI PDO</option>
                        <option>RDI PD3</option>
                        <option>RDI PD4</option>
                        <option>RDI PD5</option>
                    </select>
                </div>
                <button className={styles.saveButton} onClick={handleSave}>
                    SAVE
                </button>
            </section>
        </div>
    )
}

export default PortConfig