#include <poppler-document.h>
#include <poppler-page.h>
#include <poppler-rectangle.h>
#include <poppler-text-box.h>

#include <iostream>

void addMarkupToPage(poppler::page *page, int pageNumber)
{
    double pageWidth = page->page_rect().width();
    double pageHeight = page->page_rect().height();

    poppler::rectangle markupRect(pageWidth / 4, pageHeight - (pageHeight / 10), pageWidth / 2, pageHeight / 20);

    auto pageText = page->text(poppler::rectf({ 0, 0, pageWidth, pageHeight }));

    for (const auto &text : pageText) {
        if (text.search("Страница " + std::to_string(pageNumber)) != std::string::npos) {
            auto markupTextBox = poppler::text_box(text.bbox());
            markupTextBox.set_color(1.0, 0.0, 0.0); 
            markupTextBox.set_outline_color(0.0, 0.0, 0.0);
            page->add_annot(markupTextBox);
            break;
        }
    }
}

int main()
{
    std::string filePath = "path/to/file.pdf";
    poppler::document *doc = poppler::document::load_from_file(filePath);

    if (!doc || doc->is_locked()) {
        std::cerr << "Не удалось открыть PDF файл или он защищен паролем.\n";
        return 1;
    }

    int numPages = doc->pages();
    for (int i = 0; i < numPages; i++) {
        poppler::page *page = doc->create_page(i);
        addMarkupToPage(page, i + 1);
        delete page;
    }

    std::string outputFilePath = "path/to/output.pdf";
    doc->save_as(outputFilePath);

    delete doc;

    return 0;
}
