#include <QtGui/QtGui>
#include <QApplication>
#include <QWebEngineView>
#include <QHBoxLayout>
#include <QPlainTextEdit>
#include <fstream>

QString example()
{
    std::ifstream file("..\\QtHtmlEditor\\example.txt", std::ios::binary);
    if (file.is_open())
    {
        std::string text;
        while(!file.eof())
        {
            char output[20];
            file.read(output, sizeof(output) - 1);
            if(file.gcount() < sizeof(output) - 1)
                output[file.gcount()] = 0;
            else
                output[sizeof(output) - 1] = 0;

            for(int i = 0; output[i] != '\0'; ++i)
            {
                if (output[i] != '\n')
                    text += output[i];
            }
        }
        return QString::fromStdString(text);
    }
    return "<h1 style=\"color:#FF0000\">Hello world!</h1>";
}

class HtmlEditor : public QWidget
{
private:
    Q_OBJECT
    QHBoxLayout *hBox = nullptr;
    QPlainTextEdit *htmlEdit = nullptr;
    QWebEngineView *webView = nullptr;
public:
    HtmlEditor(QWidget *parent = nullptr);
    ~HtmlEditor();
};

HtmlEditor::HtmlEditor(QWidget *parent) : QWidget(parent)
{
    htmlEdit = new QPlainTextEdit(this);
    webView = new QWebEngineView(this);
    hBox = new QHBoxLayout(this);

    htmlEdit->setPlainText(example());
    htmlEdit->moveCursor(QTextCursor::EndOfLine);
    htmlEdit->zoomIn(3);

    webView->setHtml(htmlEdit->toPlainText());

    hBox->addWidget(htmlEdit);
    hBox->addWidget(webView);
    htmlEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    webView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    QObject::connect(htmlEdit, &QPlainTextEdit::textChanged, webView, [this]()
    {
        webView->setHtml(htmlEdit->toPlainText());
    });
}

HtmlEditor::~HtmlEditor() {}

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    HtmlEditor editor;
    editor.resize(1280, 720);
    editor.show();
    return app.exec();
}

#include "main.moc"
