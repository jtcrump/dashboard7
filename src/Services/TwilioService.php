<?php
namespace App\Services;

use Twilio\Rest\Client;

class TwilioService
{
    private $twilio;

    public function __construct()
    {
        $sid = getenv("TWILIO_ACCOUNT_SID", false);
        $token = getenv("TWILIO_AUTH_TOKEN", false);

        if (! $sid || ! $token) {
            throw new \Exception("Unable to connect to SMS Gateway: no credentials provided");
        }

        $this->twilio = new Client($sid, $token);
    }

    public function sendSms($from, $to, $message, $image=null)
    {
        $messageOptions = [
            "body" => $message,
            "from" => $from,
        ];

        if ($image && file_exists($image)) {
            $messageOptions["mediaUrl"] = $image;
        }

        try {
            $response = $this->twilio->messages->create($to, $messageOptions);
            if (! $response) {
                throw new \Exception("no response from api");
            }
            return $response;
        } catch (\Exception $e) {
            throw new \Exception("Unable to send sms message: " . $e->getMessage());
        }
    }

}

