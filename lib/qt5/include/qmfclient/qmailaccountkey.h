/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the Qt Messaging Framework.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QMAILACCOUNTKEY_H
#define QMAILACCOUNTKEY_H

#include "qmaildatacomparator.h"
#include "qmailkeyargument.h"
#include "qmailid.h"
#include "qmailmessagefwd.h"
#include <QList>
#include <QSharedData>
#include <QVariant>
#include "qmailipc.h"
#include "qmailglobal.h"

class QMailAccountKeyPrivate;

template <typename Key>
class MailKeyImpl;


class QMF_EXPORT QMailAccountKey
{
public:
    enum Property
    {
        Id = (1 << 0),
        Name = (1 << 1),
        MessageType = (1 << 2),
        FromAddress = (1 << 3),
        Status = (1 << 4),
        Custom = (1 << 5),
        LastSynchronized = (1 << 6)
    };

    typedef QMailAccountId IdType;
    typedef QMailKeyArgument<Property> ArgumentType;

    QMailAccountKey();
    QMailAccountKey(const QMailAccountKey& other);
    virtual ~QMailAccountKey();

    QMailAccountKey operator~() const;
    QMailAccountKey operator&(const QMailAccountKey& other) const;
    QMailAccountKey operator|(const QMailAccountKey& other) const;
    const QMailAccountKey& operator&=(const QMailAccountKey& other);
    const QMailAccountKey& operator|=(const QMailAccountKey& other);

    bool operator==(const QMailAccountKey& other) const;
    bool operator !=(const QMailAccountKey& other) const;

    const QMailAccountKey& operator=(const QMailAccountKey& other);

    bool isEmpty() const;
    bool isNonMatching() const;
    bool isNegated() const;

    //for subqueries
    operator QVariant() const;

    const QList<ArgumentType> &arguments() const;
    const QList<QMailAccountKey> &subKeys() const;

    QMailKey::Combiner combiner() const;

    template <typename Stream> void serialize(Stream &stream) const;
    template <typename Stream> void deserialize(Stream &stream);

    static QMailAccountKey nonMatchingKey();

    static QMailAccountKey id(const QMailAccountId &id, QMailDataComparator::EqualityComparator cmp = QMailDataComparator::Equal);
    static QMailAccountKey id(const QMailAccountIdList &ids, QMailDataComparator::InclusionComparator cmp = QMailDataComparator::Includes);
    static QMailAccountKey id(const QMailAccountKey &key, QMailDataComparator::InclusionComparator cmp = QMailDataComparator::Includes);

    static QMailAccountKey name(const QString &value, QMailDataComparator::EqualityComparator cmp = QMailDataComparator::Equal);
    static QMailAccountKey name(const QString &value, QMailDataComparator::InclusionComparator cmp);
    static QMailAccountKey name(const QStringList &values, QMailDataComparator::InclusionComparator cmp = QMailDataComparator::Includes);

    static QMailAccountKey messageType(QMailMessageMetaDataFwd::MessageType value, QMailDataComparator::EqualityComparator cmp = QMailDataComparator::Equal);
    static QMailAccountKey messageType(int value, QMailDataComparator::InclusionComparator cmp);

    static QMailAccountKey fromAddress(const QString &value, QMailDataComparator::EqualityComparator cmp = QMailDataComparator::Equal);
    static QMailAccountKey fromAddress(const QString &value, QMailDataComparator::InclusionComparator cmp);

    static QMailAccountKey lastSynchronized(const QDateTime &value, QMailDataComparator::EqualityComparator cmp = QMailDataComparator::Equal);
    static QMailAccountKey lastSynchronized(const QDateTime &value, QMailDataComparator::RelationComparator cmp);

    static QMailAccountKey status(quint64 mask, QMailDataComparator::InclusionComparator cmp = QMailDataComparator::Includes);
    static QMailAccountKey status(quint64 mask, QMailDataComparator::EqualityComparator cmp);

    static QMailAccountKey customField(const QString &name, QMailDataComparator::PresenceComparator cmp = QMailDataComparator::Present);
    static QMailAccountKey customField(const QString &name, const QString &value, QMailDataComparator::EqualityComparator cmp = QMailDataComparator::Equal);
    static QMailAccountKey customField(const QString &name, const QString &value, QMailDataComparator::InclusionComparator cmp);

private:
    QMailAccountKey(Property p, const QVariant& value, QMailKey::Comparator c);

    template <typename ListType>
    QMailAccountKey(const ListType &valueList, Property p, QMailKey::Comparator c);

    friend class QMailAccountKeyPrivate;
    friend class MailKeyImpl<QMailAccountKey>;

    QSharedDataPointer<QMailAccountKeyPrivate> d;
};

Q_DECLARE_USER_METATYPE(QMailAccountKey)

#endif
