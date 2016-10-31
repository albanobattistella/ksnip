/*
 *  Copyright (C) 2016 Damir Porobic <https://github.com/damirporobic>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 *
 */

#ifndef IMAGEUPLOADER_H
#define IMAGEUPLOADER_H

#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDomDocument>
#include <QImage>
#include <QBuffer>

class ImgurUploader : public QObject
{
    Q_OBJECT
public:
    enum Result { Successful, Error };
    
public:
    ImgurUploader ( QObject *parent = 0 );
    void startUpload ( QImage image, QByteArray accessToken = 0);
    void getAccessToken (QByteArray pin);
    void refreshToken (QByteArray refreshTocken);
    QUrl pinRequestUrl();

signals:
    void uploadFinished ( const QString message, ImgurUploader::Result result = Error );
    void tokenUpdated (const QString accessToken, const QString refreshTocken, const QString username, ImgurUploader::Result result);

private:
    QNetworkAccessManager *mAccessManager;
    QByteArray             mClientId;
    QByteArray             mClientSecret;
    void uploadAsAnonymous (QImage image);
    void uploadToAccount (QImage image, QByteArray accessToken);
    void handleDataResponse (QDomElement element);
    void handleTokenResponse (QDomElement element);
    void handleErrorResponse (QDomElement element);
    void printHeader ( QNetworkReply *reply );

private slots:
    void handleReply ( QNetworkReply *reply );
};

#endif // IMAGEUPLOADER_H