
#ifndef _SEND_EMAIL_H_
#define _SEND_EMAIL_H_

#include <Arduino.h>
#include <ESP_Mail_Client.h>

void sendEmail(const char* recipientEmail, const char* recipientName, const char* emailSubject, const char* messageText);  

void smtpCallback(SMTP_Status status);       // Get the email sending status


#endif // _SEND_EMAIL_H_
