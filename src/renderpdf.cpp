#include "headers/renderpdf.h"

RenderPdf::RenderPdf(QObject *parent) :
    QObject(parent)
{

    connect(webView.page()->mainFrame(),SIGNAL(loadFinished(bool)),this,SLOT(loadFinished(bool)));

    printer.setPrinterName("Print to File (PDF)");
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPrintRange(QPrinter::AllPages);
    printer.setOrientation(QPrinter::Portrait);
    printer.setPaperSize(QPrinter::A4);
    printer.setResolution(QPrinter::HighResolution);
    printer.setFullPage(false);
    printer.setNumCopies(1);
}

void RenderPdf::loadFinished(bool ok)
{
    if(ok) {
        webView.print(&printer);
    }
}

void RenderPdf::render(QString html, QString file)
{
    printer.setOutputFileName(file);
    webView.setHtml(html);

}

