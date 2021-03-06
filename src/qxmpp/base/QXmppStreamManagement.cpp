#include "QXmppStreamManagement.h"

#include "../client/QXmppConfiguration.h"
#include <QDomElement>
#include <qxmlstream.h>
#include "QXmppConstants.h"


class QXmppStreamManagementPrivate
{
public:
    QXmppStreamManagementPrivate();
    QXmppConfiguration::StreamManagementMode streamManagementMode;
    bool outboundEnabled;
    bool inboundEnabled;
    bool resumeEnabled;
    QString resumeId;
    QString resumeLocation;
    int  outboundCounter;
    int  inboundCounter;
    int  lastHandleStanzaSent;
    bool resumming;
    QMap <int, QXmppStanza*> outboundBuffer;

};

QXmppStreamManagementPrivate::QXmppStreamManagementPrivate()
    : streamManagementMode(QXmppConfiguration::SMDisabled)
    , outboundEnabled(false)
    , inboundEnabled(false)
    , resumeEnabled(false)
    , outboundCounter(0)
    , inboundCounter(0)
{

}

QXmppStreamManagement::QXmppStreamManagement(QObject *parent)
    : QXmppLoggable(parent)
    , d(new QXmppStreamManagementPrivate)
{
}

void QXmppStreamManagement::enableSent()
{
    d->outboundEnabled = true;
    d->outboundCounter = 0;
}

void QXmppStreamManagement::enabledReceived(const QDomElement &element)
{
    d->inboundEnabled = true;
    if(element.hasAttribute("id"))
        d->resumeId = element.attribute("id");
    if(element.hasAttribute("location"))
        d->resumeLocation = element.attribute("location");
    if(element.hasAttribute("resume"))
    {
        if(element.attribute("resume") == "true")
            d->resumeEnabled = true;
    }
    d->inboundCounter = 0;
}

void QXmppStreamManagement::disable()
{
    d->inboundCounter = 0;
    d->inboundEnabled = false;
    d->outboundCounter = 0;
    d->outboundEnabled = false;
    d->outboundBuffer.clear();
    d->resumeEnabled = false;
    d->resumeId.clear();
    d->resumeLocation.clear();
    d->resumming = false;
    d->lastHandleStanzaSent = 0;
}

void QXmppStreamManagement::stanzaSent(const QXmppStanza &stanza)
{
    d->outboundCounter++;
    debug(QString("SM STANZA SENT outbound counter:%1").arg(QString::number(d->outboundCounter)));
    switch(stanza.getStanzaType())
    {
    case QXmppStanza::Message:
    {
        QXmppMessage *message = new QXmppMessage(static_cast<QXmppMessage const &>(stanza));
        d->outboundBuffer.insert(d->outboundCounter, message);
        break;
    }
    case QXmppStanza::Iq:
    {
        QXmppIq *iq = new QXmppIq(static_cast<QXmppIq const &>(stanza));
        d->outboundBuffer.insert(d->outboundCounter, iq);
        break;
    }
    case QXmppStanza::Presence:
    {
        QXmppPresence *presence = new QXmppPresence(static_cast<QXmppPresence const &>(stanza));
        d->outboundBuffer.insert(d->outboundCounter, presence);
        break;
    }
    default:
        break;
    }
}

void QXmppStreamManagement::ackReceived(const QDomElement &element)
{
    const QString h = element.attribute("h");
    debug(QString("SM ACK RECV h=%1 outbound count=%2").arg(h).arg(QString::number(d->outboundCounter)));
    int handled = h.toInt();

    QMapIterator <int, QXmppStanza*> i(d->outboundBuffer);
    const QXmppStanza *stanza = NULL;
    while (i.hasNext()) {
        i.next();
        if(i.key()<= handled)
        {
            stanza = i.value();
            switch (stanza->getStanzaType())
            {
                case QXmppStanza::Message:
                {
                    QXmppMessage message(static_cast<QXmppMessage const &> (*stanza));
                    emit messageAcknowledged(message, true);
                    break;
                }
                case QXmppStanza::Iq:
                {
                    QXmppIq iq(static_cast<QXmppIq const &> (*stanza));
                    emit iqAcknowledged(iq, true);
                    break;
                }
                case QXmppStanza::Presence:
                {
                    QXmppPresence presence(static_cast<QXmppPresence const &>(*stanza));
                    emit presenceAcknowledged(presence, true);
                    break;
                }
                default:
                    break;
           }

           d->outboundBuffer.remove(i.key());
           delete stanza;
           debug(QString("SM h:%1 removed from the buffer").arg(i.key()));
       }
    }
}

void QXmppStreamManagement::resumeSent()
{
    d->resumming = true;
}

void QXmppStreamManagement::resumedReceived()
{
    if(d->resumming)
    {
        d->resumming = false;
    }
}

void QXmppStreamManagement::failedReceived(const QDomElement &element, QXmppStanza::Error::Condition &condition)
{
    QXmppStanza::Error error;
    error.parse(element);
    condition = error.condition();
    d->resumeEnabled = false;
    d->inboundCounter = false;
    d->outboundEnabled = false;
    /// TO-DO if resume failed the buffer has to be emptied notifying the packets that couldn't be acknoledged.
    d->resumming = false;
}

void QXmppStreamManagement::stanzaHandled()
{
    d->inboundCounter++;
}

void QXmppStreamManagement::enableToXml(QXmlStreamWriter *xmlStream, const bool resume)
{
    xmlStream->writeStartElement("enable");
    xmlStream->writeAttribute("xmlns",ns_stream_management);
    if(resume)
    {
        xmlStream->writeAttribute("resume","true");
    }
    xmlStream->writeEndElement();
}

void QXmppStreamManagement::ackToXml(QXmlStreamWriter *xmlStream)
{
    d->lastHandleStanzaSent = d->inboundCounter;
    xmlStream->writeStartElement("a");
    xmlStream->writeAttribute("xmlns",ns_stream_management);
    xmlStream->writeAttribute("h", QString::number(d->inboundCounter));
    xmlStream->writeEndElement();
}

void QXmppStreamManagement::requestToXml(QXmlStreamWriter *xmlStream)
{
    xmlStream->writeStartElement("r");
    xmlStream->writeAttribute("xmlns",ns_stream_management);
    xmlStream->writeEndElement();
}

void QXmppStreamManagement::resumeToXml(QXmlStreamWriter *xmlStream)
{
    xmlStream->writeStartElement("resume");
    xmlStream->writeAttribute("xmlns",ns_stream_management);
    xmlStream->writeAttribute("h", QString::number(d->lastHandleStanzaSent));
    xmlStream->writeAttribute("previd", d->resumeId);
    xmlStream->writeEndElement();
}

bool QXmppStreamManagement::isEnabled() const
{
    return (d->inboundEnabled && d->outboundEnabled);
}

bool QXmppStreamManagement::isOutboundEnabled() const
{
    return d->outboundEnabled;
}

bool QXmppStreamManagement::isInboundEnabled() const
{
    return d->inboundEnabled;
}

bool QXmppStreamManagement::isResumeEnabled() const
{
    return d->resumeEnabled;
}

bool QXmppStreamManagement::isResumming() const
{
    return d->resumming;
}

int QXmppStreamManagement::outboundCounter() const
{
    return d->outboundCounter;
}

int QXmppStreamManagement::inboudCounter() const
{
    return d->inboundCounter;
}

QString QXmppStreamManagement::resumeId() const
{
    return d->resumeId;
}

QString QXmppStreamManagement::resumeLocation() const
{
    return d->resumeLocation;
}

QList<QXmppStanza*> QXmppStreamManagement::outBoundBuffer() const
{
   return d->outboundBuffer.values();
}

void QXmppStreamManagement::socketDisconnected()
{
    // If resume is enabled the buffer is not emptied until the resume is attempted
    if(!d->resumeEnabled)
    {
        QMapIterator <int, QXmppStanza*> i(d->outboundBuffer);
        const QXmppStanza *stanza = NULL;
        while (i.hasNext()) {
            i.next();
            stanza = i.value();
            switch (stanza->getStanzaType())
            {
                case QXmppStanza::Message:
                {
                    QXmppMessage message(static_cast<QXmppMessage const &> (*stanza));
                    emit messageAcknowledged(message, false);
                    break;
                }
                case QXmppStanza::Iq:
                {
                    QXmppIq iq(static_cast<QXmppIq const &> (*stanza));
                    emit iqAcknowledged(iq, false);
                    break;
                }
                case QXmppStanza::Presence:
                {
                    QXmppPresence presence(static_cast<QXmppPresence const &>(*stanza));
                    emit presenceAcknowledged(presence, false);
                    break;
                }
                default:
                    break;
            }
            d->outboundBuffer.remove(i.key());
            delete stanza;
            debug(QString("SM h:%1 removed from the buffer").arg(i.key()));
        }
    }else{
        d->resumming = true;
    }


}
