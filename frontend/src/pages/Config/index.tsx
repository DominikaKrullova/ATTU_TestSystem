import React, { useEffect, useState } from 'react';
import { useDispatch, useSelector } from 'react-redux';
import { RootState } from '../../store/store';
import PortConfig from './PortConfig';
import Modal from '../../components/Modal/Modal';
import { ATTU, Port } from '../../model/dataModels';
import styles from './Config.module.scss'
import { addATTU } from '../../store/slices/attuSlice';
import Ports from './Ports';
import classNames from 'classnames';

const ATTUConfigPage = () => {

    const attuList = useSelector((state: RootState) => state.attuReducer.attus);
    const dispatch = useDispatch();

    const [isOpen, setIsOpen] = useState<boolean>(false);
    const [attuIp, setAttuIp] = useState<string>("");
    const [networkPort, setNetworkPort] = useState<number>();

    const [selectedATTU, setSelectedATTU] = useState<ATTU>();
    const [selectedPort, setSelectedPort] = useState<Port>();


    useEffect(() => {
        if (selectedPort) {
            setIsOpen(true);
        }
    }, [selectedPort]);

    const closeModal = () => {
        setIsOpen(false);
    }


    const handleAddAttu = () => {
        dispatch(
            addATTU({ attuIp, networkPort })
        )
    }


    return (
        <>
            <div>
                <h1>ATTU Config</h1>
            </div>
            <div className={styles.pageContainer}>
                <div className={styles.row}>
                    <div className={styles.attuListPanel}>
                        <h5>ATTUs</h5>
                        <div className={styles.attuListContainer}>
                            <ul>
                                {attuList.map((attu) => (
                                    <button onClick={() => (setSelectedATTU(attu))} key={attu.attuIp} className={classNames(styles.attuListItem, { [styles.selectedAttu]: selectedATTU?.attuIp === attu.attuIp })}>
                                        {attu.attuIp}:{attu.networkPort}
                                    </button>
                                ))}
                            </ul>
                        </div>
                    </div>
                    {selectedATTU ? <Ports selectedATTU={selectedATTU} ports={selectedATTU?.ports} setSelectedPort={setSelectedPort} /> : <div className={styles.portsPlaceholder}>Select an ATTU to view its ports</div>}
                </div>
                <div className={styles.addAttu}>
                    <h3>ATTU IP Configuration</h3>
                    <label htmlFor='attuIp'>IP Address</label>
                    <input
                        name='attuIp'
                        type="text"
                        value={attuIp}
                        onChange={(e) => setAttuIp(e.target.value)}
                    />
                    <label htmlFor='networkPort'>Network Port</label>
                    <input
                        name='networkPort'
                        type="number"
                        value={networkPort}
                        onChange={(e) => setNetworkPort(Number(e.target.value))}
                    />
                    <button disabled={!attuIp || !networkPort} onClick={handleAddAttu}>Add</button>
                </div>
            </div >
            {isOpen && (
                <Modal title='Port Config' onClose={closeModal} isOpen={isOpen}>
                    <PortConfig onClose={closeModal} attu={selectedATTU} port={selectedPort} />
                </Modal>)
            }


        </>
    );
};

export default ATTUConfigPage;
