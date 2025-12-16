import { jsPDF } from "jspdf";
import autoTable from "jspdf-autotable";
import { Test } from "../../model/dataModels";
import styles from './pdfGenerator.module.scss'

export function PdfButton({ tests }: { tests: Test[] }) {
  const disabled = tests.some(t => t.status === "isRunning") || tests.length === 0;
  const generatePdf = () => {
    const doc = new jsPDF();
    doc.text("Test Report", 14, 16);

    autoTable(doc, {
      startY: 22,
      head: [["Name", "Attu Ip", "Port", "Result"]],
      body: tests.map(t => [t.testName, t.attuIp, t.port.portNumber, t.status ?? "Failed"]),
    });

    doc.save("test-report.pdf");
  };

  return <button className={styles.button} disabled={disabled}
    onClick={generatePdf}>Generate PDF</button>;
}
