#include "sourceloadinglistener.h"

#include "util/urlutil.h"
#include "util/fileutil.h"
#include <QDebug>

namespace artemis {

SourceLoadingListener::SourceLoadingListener()
{
    qDebug() << "SLL: CODE INIT" << endl;
    this->src_idx = 0;
    this->file_idx = 0;
    create_dir(".","js-code-dump");
}

void SourceLoadingListener::code_loaded(QString source, QUrl url, int startline) {

    if (this->visisted.contains(get_hash(url,startline)) || is_omit(url)) {
        return;
    }
    visisted << get_hash(url,startline);
    locs.insert(get_hash(url,startline), qMakePair(url,startline));
    size_of_code.insert(get_hash(url,startline), source.toAscii().size());
    QString name = "js" + QString::number(src_idx++) + ".js";
    write_string_to_file("js-code-dump/" + name, source);
    this->rewrite_urls.insert(url.toString(),name);
}

void SourceLoadingListener::print_results() {
    unsigned long total_loaded = 0;
    foreach (int hash, this->size_of_code.keys()) {
        QUrl url = locs[hash].first;
        int startline = locs[hash].second;
        total_loaded += size_of_code[hash];
        qDebug() << "(" << url << "," << QString::number(startline) << ")  ->  " << QString::number(size_of_code[hash]) << "b";
    }
    qDebug() << "Total loaded code: " << total_loaded << " bytes";
}

void SourceLoadingListener::loaded_page(const ArtemisWebPage& page, ExecutorState* exe_state)
{
    write_string_to_file("js-code-dump/pagestate" + QString::number(this->file_idx++) + ".html", page.mainFrame()->toHtml());
}

}
