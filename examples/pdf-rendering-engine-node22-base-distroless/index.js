import express from 'express';
import PDFDocument from 'pdfkit';

const app = express();
app.use(express.json());

app.post('/render', (req, res) => {
  const { title, content } = req.body;
  const doc = new PDFDocument();

  res.setHeader('Content-Type', 'application/pdf');
  res.setHeader('Content-Disposition', 'attachment; filename=document.pdf');

  doc.pipe(res);
  doc.fontSize(24).text(title || 'Invoice', 100, 80);
  doc.fontSize(12).text(content || 'No content provided.', 100, 130);
  doc.end();
});

app.listen(3000, '0.0.0.0');
