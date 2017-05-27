#include "scs.h"
#include "ui_scs.h"
#include <QFileDialog>
#include <QTextStream>

QString fn;

SCS::SCS(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SCS)
{
    ui->setupUi(this);
}

SCS::~SCS()
{
    delete ui;
}

void SCS::on_solve_clicked()
{
    QString Cs(ui->Cs->text());
    QString Ss(ui->Ss->text());
    input infile(ui->section->toPlainText(),Cs.toDouble(),Ss.toDouble());
    for (int i = 0; i != infile.sec().size(); ++i)
        ui->figure1->setModel(infile.sec());
    m_psec = infile.sec();
    m_M_phi.clear();
    double neutop(0);
    double neubot(0);
    for (int i = 0; i != m_psec.size(); ++i)
    {
        neutop = qMax(neutop, m_psec[i]->y());
        neubot = qMin(neubot, m_psec[i]->y());
    }
    double neu(0);
    double dphi(0.0000001);
    double phi(0);
    double N(0);
    QString Ns(ui->N->text());
    double Nd(Ns.toDouble()*1000);
    double M(0);
    QVector<double> tmp;
    tmp<<0;
    tmp<<0;
    m_M_phi<<tmp;
    int mark(0);
    int k(0);
    int mmark(0);
    while(phi <= 0.000035)
    {
        mark = 0;
        k = 0;
        phi += dphi;
        double nt(10*neutop);
        double nb(10*neubot);
        do
        {
            N = 0;
            neu = (nt + nb)/2;
            for (int i = 0; i != m_psec.size(); ++i)
                N += (m_psec[i]->stress(phi*(neu - m_psec[i]->y())))*(m_psec[i]->A());
            if(N - Nd > 0) nt = neu;
            else nb = neu;
            ++k;
            if (k>100) mark = 1;
        }while(qAbs(N - Nd) > 1 && mark == 0);
        M = 0;
        for (int i = 0; i != m_psec.size(); ++i)
        {
            M += (neu - m_psec[i]->y())*(m_psec[i]->stress(phi*(neu - m_psec[i]->y())))*(m_psec[i]->A());
        }
        if (mark == 0)
        {
            QVector<double> tmp;
            tmp<<M;
            tmp<<phi;
            m_M_phi<<tmp;
        }
        else mmark = 1;
    }
    if (mmark == 0) ui->graph1->setModel(m_M_phi);
    else
    {
        QVector<QVector<double> > co;
        ui->graph1->setModel(co);
    }
}

void SCS::on_section_textChanged()
{
    input infile(ui->section->toPlainText());
    ui->figure1->setModel(infile.sec());
}

void SCS::on_output_clicked()
{
    QString output;
    output += "phi,M(kNm)\r\n";
    for(int i = 0; i != m_M_phi.size(); ++i)
        output += QString::number(m_M_phi[i][1]/1000000) + "," + QString::number(m_M_phi[i][0]) + "\r\n";
    QString fileName = QFileDialog::getSaveFileName(this, tr("Output"), "", tr("CSV File (*.csv)"));
    if (!fileName.isEmpty())
    {
        if(!fileName.endsWith(".csv", Qt::CaseInsensitive))
            fileName = fileName + ".csv";
        else
            fileName = fileName;
        QFile file(fileName);
        file.open(QFile::WriteOnly);
        QTextStream out(&file);
        out<<output;
        file.close();
    }
}

void SCS::on_actionNew_triggered()
{
    ui->section->clear();
    fn = "";
}

void SCS::on_actionSave_triggered()
{
    if(fn.isEmpty())
    {
        on_actionSave_as_triggered();
    }
    else
    {
        QFile file(fn);
        file.open(QFile::WriteOnly);
        QTextStream out(&file);
        out<<ui->section->toPlainText();
        out<<";" + ui->N->text() + ";" + ui->Cs->text() + ";" + ui->Ss->text();
        file.close();
    }
}

void SCS::on_actionSave_as_triggered()
{
    QString fileName(QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("Section Model (*.scs)")));
    if (!fileName.isEmpty())
    {
        if(!fileName.endsWith(".scs", Qt::CaseInsensitive))
            fn = fileName + ".scs";
        else
            fn = fileName;
        on_actionSave_triggered();
    }
}


void SCS::on_actionImport_triggered()
{
    fn = QFileDialog::getOpenFileName(this, tr("Import File"), "", tr("Section Model (*.scs)"));
    if(!fn.isEmpty())
    {
        QFile file(fn);
        file.open(QFile::ReadOnly);
        QTextStream in(&file);
        QString ins(in.readAll());
        ui->section->setPlainText(ins.section(";",0,0));
        ui->N->setText(ins.section(";",1,1));
        ui->Cs->setText(ins.section(";",2,2));
        ui->Ss->setText(ins.section(";",3,3));
        file.close();
    }
}
