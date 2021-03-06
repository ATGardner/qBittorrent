/*
 * Bittorrent Client using Qt and libtorrent.
 * Copyright (C) 2016 Eugene Shalygin
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * In addition, as a special exception, the copyright holders give permission to
 * link this program with the OpenSSL project's "OpenSSL" library (or with
 * modified versions of it that use the same license as the "OpenSSL" library),
 * and distribute the linked executables. You must obey the GNU General Public
 * License in all respects for all of the code used other than "OpenSSL".  If you
 * modify file(s), you may extend this exception to your version of the file(s),
 * but you are not obligated to do so. If you do not wish to do so, delete this
 * exception statement from your version.
 */

#ifndef QBT_GUI_FSPATHEDIT_P_H
#define QBT_GUI_FSPATHEDIT_P_H

#include <QAction>
#include <QComboBox>
#include <QCompleter>
#include <QContextMenuEvent>
#include <QDir>
#include <QFileIconProvider>
#include <QFileSystemModel>
#include <QKeyEvent>
#include <QLineEdit>
#include <QMenu>

namespace Private
{
    class FileEditorWithCompletion
    {
    public:
        virtual ~FileEditorWithCompletion() = default;
        virtual void completeDirectoriesOnly(bool completeDirsOnly) = 0;
        virtual void setFilenameFilters(const QStringList &filters) = 0;
        virtual void setBrowseAction(QAction *action) = 0;
        virtual QWidget *widget() = 0;
    };

    class FileLineEdit: public QLineEdit, public FileEditorWithCompletion
    {
        Q_OBJECT
        Q_DISABLE_COPY(FileLineEdit)

    public:
        FileLineEdit(QWidget *parent = nullptr);
        ~FileLineEdit();

        void completeDirectoriesOnly(bool completeDirsOnly) override;
        void setFilenameFilters(const QStringList &filters) override;
        void setBrowseAction(QAction *action) override;
        QWidget *widget() override;

    protected:
        void keyPressEvent(QKeyEvent *event) override;
        void contextMenuEvent(QContextMenuEvent *event) override;

    private slots:
        void showCompletionPopup();

    private:
        QFileSystemModel *m_completerModel;
        QCompleter *m_completer;
        QAction *m_browseAction;
        QFileIconProvider m_iconProvider;
    };


    class FileComboEdit: public QComboBox, public FileEditorWithCompletion
    {
        Q_OBJECT

    public:
        FileComboEdit(QWidget *parent = nullptr);

        void completeDirectoriesOnly(bool completeDirsOnly) override;
        void setFilenameFilters(const QStringList &filters) override;
        void setBrowseAction(QAction *action) override;
        QWidget *widget() override;

    protected:
        QString text() const;
    };
}

#endif // QBT_GUI_FSPATHEDIT_P_H
