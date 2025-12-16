import React from 'react'
import styles from './SideBar.module.scss'
import { createBrowserRouter, Link, useNavigate } from 'react-router-dom'


interface SideBarProps {
    connectionStatus: string
}

const SideBar: React.FC<SideBarProps> = ({ connectionStatus }) => {

    const navigate = useNavigate();
    const goToPage = (path: string) => {
        navigate(path);
    };
    return (
        <div className={styles.sideBar}>
            <div>
                <h1 onClick={() => goToPage('/')}>ATTU TEST SYSTEM</h1>
            </div>
            <div className={styles.navLinks}>
                <h3 onClick={() => goToPage('/config')}>Config</h3>
                <h3 onClick={() => goToPage('/tests')}>Tests</h3>
                <h3 className={styles.connection}>
                    WS: {connectionStatus}
                </h3>

            </div>



        </div>
    )
}

export default SideBar