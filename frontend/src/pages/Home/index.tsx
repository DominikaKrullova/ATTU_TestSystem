import styles from "./Home.module.scss";

export default function Home() {
  return (
    <div className={styles.container}>
      <h1 className={styles.title}>👋 Welcome to the ATTU TEST SYSTEM</h1>

      <p className={styles.paragraph}>
        This application allows you to run, and monitor tests on ATTU devices
      </p>
      <section className={styles.section}>
        <h2 className={styles.subtitle}>⚙️ Configure ATTU Connection</h2>
        <ul className={styles.list}>
          <li>Enter the ATTU device IP address in the configuration panel</li>
          <li>Provide the port number that the ATTU will communicate through</li>
          <li>Ensure the IP and port match your network/device settings</li>
          <li>Save the configuration before running or creating tests</li>
        </ul>
      </section>
      <section className={styles.section}>
        <h2 className={styles.subtitle}>⚙️ Configure ATTU PORTS</h2>
        <ul className={styles.list}>
          <li>Select an ATTU from the list</li>
          <li>Select the port to configure</li>
          <li>Configure the port settings as needed</li>
          <li>Save the configuration before running or creating tests</li>
        </ul>
      </section>
      <section className={styles.section}>
        <h2 className={styles.subtitle}>✅ Run Tests</h2>
        <ul className={styles.list}>
          <li>Select a test</li>
          <li>Provide the ATTU IP address</li>
          <li>Enter the port number</li>
          <li>Add test to queue</li>
        </ul>
      </section>
    </div>
  );
}
