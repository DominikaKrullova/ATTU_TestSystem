import React, { useState } from 'react'
import styles from './Menu.module.scss'
import { useDispatch, useSelector } from 'react-redux';
import { RootState } from '../../../store/store';
import { ATTU, Port, Test, TestStartRequest } from '../../../model/dataModels';
import Modal from '../../../components/Modal/Modal';
import PortConfig from '../../Config/PortConfig';
import classNames from 'classnames';
import { startTestWs } from '../../../service/testService';
import { useAppWebSocket } from '../../../hooks/useAppWebSocket';

const Menu = () => {

    const tests = ["Data Corruption Test", "Packet Loss Test"];

    const attuList = useSelector((state: RootState) => state.attuReducer.attus);

    const [selectedATTU, setSelectedATTU] = useState<ATTU>();
    const [selectedPort, setSelectedPort] = useState<Port>();
    const [selectedTest, setSelectedTest] = useState<string>("Data Corruption Test");


    const { sendJsonMessage } = useAppWebSocket();
    const dispatch = useDispatch();

    const startTest = () => {
        if (!selectedATTU || !selectedPort || !selectedTest) return;
        const newTest = {
            testName: selectedTest,
            attuIp: selectedATTU.attuIp,
            networkPort: selectedATTU.networkPort,
            port: selectedPort
        };
        try {
            startTestWs(newTest, sendJsonMessage, dispatch);
        } catch (error) {
            throw Error("Start Test Failed!")
        }
    };



    const [isOpen, setIsOpen] = useState<boolean>(false);
    const closeModal = () => {
        setIsOpen(false);
    }

    const openModal = () => {
        setIsOpen(true);
    }

    return (
        <div className={styles.menuPanel}>
            <h3 className={styles.title}>Menu</h3>
            <div className={styles.menuContainer}>
                <div className={styles.rowFull}>
                    <select className={classNames(styles.select, styles.testSelect)} value={selectedTest ?? "Pick a test"}
                        onChange={(e) => {
                            const test = e.target.value;
                            setSelectedTest(test);
                        }}>
                        {tests.map((test) => (
                            <option key={test} value={test}>{test}</option>
                        ))}
                    </select>
                </div>
                <div className={styles.rowTwo}>
                    <select
                        className={styles.select}
                        value={selectedATTU?.attuIp ?? ""}
                        onChange={(e) => {
                            const ip = e.target.value;
                            const attu = attuList.find((a) => a.attuIp === ip);
                            setSelectedATTU(attu);
                        }}
                    >
                        <option value="">Select ATTU</option>
                        {attuList.map((attu) => (
                            <option key={attu.attuIp} value={attu.attuIp}>
                                {attu.attuIp}
                            </option>
                        ))}
                    </select>
                    <select
                        className={styles.select}
                        value={selectedPort?.portNumber ?? ""}
                        onChange={(e) => {
                            const num = Number(e.target.value);
                            const port = selectedATTU?.ports.find((p) => p.portNumber === num);
                            setSelectedPort(port);
                        }}
                    >
                        <option value="">Select port</option>
                        {selectedATTU?.ports.map((port) => (
                            <option key={port.portNumber} value={port.portNumber}>
                                {port.portNumber}
                            </option>
                        ))}
                    </select>

                </div>


                <div className={styles.buttons}>
                    <button className={styles.button} disabled={!selectedATTU || !selectedPort} onClick={openModal}>Config</button>
                    <button className={styles.button} disabled={!selectedATTU || !selectedPort || !selectedTest} onClick={startTest}>Add to Queue</button>
                </div>
            </div>

            {isOpen && (
                <Modal title='Port Config' onClose={closeModal} isOpen={isOpen}>
                    <PortConfig onClose={closeModal} attu={selectedATTU} port={selectedPort} />
                </Modal>)}
        </div>

    )
}

export default Menu

