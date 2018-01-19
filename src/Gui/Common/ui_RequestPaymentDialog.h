/********************************************************************************
** Form generated from reading UI file 'RequestPaymentDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REQUESTPAYMENTDIALOG_H
#define UI_REQUESTPAYMENTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include "Gui/Common/QRLabel.h"
#include "Gui/Common/WalletBlueButton.h"
#include "Gui/Common/WalletCancelButton.h"
#include "Gui/Common/WalletLinkLikeButton.h"
#include "Gui/Common/WalletTextLabel.h"

QT_BEGIN_NAMESPACE

class Ui_RequestPaymentDialog
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *createGroupBox;
    QGridLayout *gridLayout;
    WalletGui::WalletNormalGrayTextLabel *label_2;
    QSpacerItem *horizontalSpacer_2;
    WalletGui::WalletNormalGrayTextLabel *label;
    WalletGui::WalletNormalGrayTextLabel *label_3;
    QDoubleSpinBox *m_amountSpinBox;
    QLineEdit *m_payerLabelEdit;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *m_paymentIdEdit;
    WalletGui::WalletNormalLinkLikeButton *m_generateIdButton;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    WalletGui::QRLabel *m_qrCodeLabel;
    QVBoxLayout *verticalLayout_2;
    QTextEdit *m_requestEdit;
    WalletGui::WalletLargeBlueButton *m_generateButton;
    WalletGui::WalletNormalBlueButton *m_saveQrButton;
    WalletGui::WalletNormalBlueButton *m_saveRequestButton;
    WalletGui::WalletNormalBlueButton *m_copyButton;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    WalletGui::WalletCancelButton *m_closeButton;

    void setupUi(QDialog *RequestPaymentDialog)
    {
        if (RequestPaymentDialog->objectName().isEmpty())
            RequestPaymentDialog->setObjectName(QStringLiteral("RequestPaymentDialog"));
        RequestPaymentDialog->setWindowModality(Qt::ApplicationModal);
        RequestPaymentDialog->resize(620, 570);
        verticalLayout = new QVBoxLayout(RequestPaymentDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        createGroupBox = new QGroupBox(RequestPaymentDialog);
        createGroupBox->setObjectName(QStringLiteral("createGroupBox"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(createGroupBox->sizePolicy().hasHeightForWidth());
        createGroupBox->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(createGroupBox);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_2 = new WalletGui::WalletNormalGrayTextLabel(createGroupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(299, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 3, 1, 1);

        label = new WalletGui::WalletNormalGrayTextLabel(createGroupBox);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_3 = new WalletGui::WalletNormalGrayTextLabel(createGroupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        m_amountSpinBox = new QDoubleSpinBox(createGroupBox);
        m_amountSpinBox->setObjectName(QStringLiteral("m_amountSpinBox"));
        m_amountSpinBox->setDecimals(12);
        m_amountSpinBox->setMaximum(1e+9);

        gridLayout->addWidget(m_amountSpinBox, 1, 2, 1, 1);

        m_payerLabelEdit = new QLineEdit(createGroupBox);
        m_payerLabelEdit->setObjectName(QStringLiteral("m_payerLabelEdit"));

        gridLayout->addWidget(m_payerLabelEdit, 0, 2, 1, 2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        m_paymentIdEdit = new QLineEdit(createGroupBox);
        m_paymentIdEdit->setObjectName(QStringLiteral("m_paymentIdEdit"));

        horizontalLayout_3->addWidget(m_paymentIdEdit);

        m_generateIdButton = new WalletGui::WalletNormalLinkLikeButton(createGroupBox);
        m_generateIdButton->setObjectName(QStringLiteral("m_generateIdButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(m_generateIdButton->sizePolicy().hasHeightForWidth());
        m_generateIdButton->setSizePolicy(sizePolicy1);
        m_generateIdButton->setMinimumSize(QSize(80, 0));
        m_generateIdButton->setFlat(true);

        horizontalLayout_3->addWidget(m_generateIdButton);


        gridLayout->addLayout(horizontalLayout_3, 2, 2, 1, 2);


        verticalLayout->addWidget(createGroupBox);

        groupBox = new QGroupBox(RequestPaymentDialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        QSizePolicy sizePolicy2(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy2);
        groupBox->setMinimumSize(QSize(600, 350));
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        m_qrCodeLabel = new WalletGui::QRLabel(groupBox);
        m_qrCodeLabel->setObjectName(QStringLiteral("m_qrCodeLabel"));
        m_qrCodeLabel->setMinimumSize(QSize(300, 300));

        horizontalLayout->addWidget(m_qrCodeLabel);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        m_requestEdit = new QTextEdit(groupBox);
        m_requestEdit->setObjectName(QStringLiteral("m_requestEdit"));

        verticalLayout_2->addWidget(m_requestEdit);

        m_generateButton = new WalletGui::WalletLargeBlueButton(groupBox);
        m_generateButton->setObjectName(QStringLiteral("m_generateButton"));
        QSizePolicy sizePolicy3(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(m_generateButton->sizePolicy().hasHeightForWidth());
        m_generateButton->setSizePolicy(sizePolicy3);
        m_generateButton->setMinimumSize(QSize(150, 0));
        m_generateButton->setFlat(true);

        verticalLayout_2->addWidget(m_generateButton);

        m_saveQrButton = new WalletGui::WalletNormalBlueButton(groupBox);
        m_saveQrButton->setObjectName(QStringLiteral("m_saveQrButton"));
        sizePolicy3.setHeightForWidth(m_saveQrButton->sizePolicy().hasHeightForWidth());
        m_saveQrButton->setSizePolicy(sizePolicy3);
        m_saveQrButton->setMinimumSize(QSize(100, 0));
        m_saveQrButton->setFlat(true);

        verticalLayout_2->addWidget(m_saveQrButton);

        m_saveRequestButton = new WalletGui::WalletNormalBlueButton(groupBox);
        m_saveRequestButton->setObjectName(QStringLiteral("m_saveRequestButton"));
        sizePolicy3.setHeightForWidth(m_saveRequestButton->sizePolicy().hasHeightForWidth());
        m_saveRequestButton->setSizePolicy(sizePolicy3);
        m_saveRequestButton->setMinimumSize(QSize(100, 0));
        m_saveRequestButton->setFlat(true);

        verticalLayout_2->addWidget(m_saveRequestButton);

        m_copyButton = new WalletGui::WalletNormalBlueButton(groupBox);
        m_copyButton->setObjectName(QStringLiteral("m_copyButton"));
        sizePolicy3.setHeightForWidth(m_copyButton->sizePolicy().hasHeightForWidth());
        m_copyButton->setSizePolicy(sizePolicy3);
        m_copyButton->setMinimumSize(QSize(100, 0));
        m_copyButton->setFlat(true);

        verticalLayout_2->addWidget(m_copyButton);


        horizontalLayout->addLayout(verticalLayout_2);


        verticalLayout->addWidget(groupBox);

        verticalSpacer = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        m_closeButton = new WalletGui::WalletCancelButton(RequestPaymentDialog);
        m_closeButton->setObjectName(QStringLiteral("m_closeButton"));
        m_closeButton->setFlat(true);

        horizontalLayout_2->addWidget(m_closeButton);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(RequestPaymentDialog);
        QObject::connect(m_closeButton, SIGNAL(clicked()), RequestPaymentDialog, SLOT(accept()));
        QObject::connect(m_generateButton, SIGNAL(clicked()), RequestPaymentDialog, SLOT(generateRequest()));
        QObject::connect(m_generateIdButton, SIGNAL(clicked()), RequestPaymentDialog, SLOT(generatePaymentIdClicked()));
        QObject::connect(m_copyButton, SIGNAL(clicked()), RequestPaymentDialog, SLOT(copyRequest()));
        QObject::connect(m_saveQrButton, SIGNAL(clicked()), RequestPaymentDialog, SLOT(saveQrCode()));
        QObject::connect(m_saveRequestButton, SIGNAL(clicked()), RequestPaymentDialog, SLOT(saveRequest()));

        QMetaObject::connectSlotsByName(RequestPaymentDialog);
    } // setupUi

    void retranslateUi(QDialog *RequestPaymentDialog)
    {
        RequestPaymentDialog->setWindowTitle(QApplication::translate("RequestPaymentDialog", "Create Payment Request", Q_NULLPTR));
        createGroupBox->setTitle(QApplication::translate("RequestPaymentDialog", "Create Request", Q_NULLPTR));
        label_2->setText(QApplication::translate("RequestPaymentDialog", "AMOUNT", Q_NULLPTR));
        label->setText(QApplication::translate("RequestPaymentDialog", "LABEL", Q_NULLPTR));
        label_3->setText(QApplication::translate("RequestPaymentDialog", "PAYMENT ID", Q_NULLPTR));
        m_generateIdButton->setText(QApplication::translate("RequestPaymentDialog", "Generate", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("RequestPaymentDialog", "Payment Request", Q_NULLPTR));
        m_qrCodeLabel->setText(QString());
        m_generateButton->setText(QApplication::translate("RequestPaymentDialog", "GENERATE REQUEST", Q_NULLPTR));
        m_saveQrButton->setText(QApplication::translate("RequestPaymentDialog", "Save QR Code", Q_NULLPTR));
        m_saveRequestButton->setText(QApplication::translate("RequestPaymentDialog", "Save Request", Q_NULLPTR));
        m_copyButton->setText(QApplication::translate("RequestPaymentDialog", "Copy to clipboard", Q_NULLPTR));
        m_closeButton->setText(QApplication::translate("RequestPaymentDialog", "Close", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class RequestPaymentDialog: public Ui_RequestPaymentDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REQUESTPAYMENTDIALOG_H
