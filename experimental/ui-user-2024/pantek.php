<?php
    // Update the path below to your autoload.php,
    // see https://getcomposer.org/doc/01-basic-usage.md
    require_once '/path/to/vendor/autoload.php';
    use Twilio\Rest\Client;

    $sid    = "AC46faa6c1f6f2c135a0b4d8956852a910";
    $token  = "f5692b6eb7abc949f8aebd166ca515c0";
    $twilio = new Client($sid, $token);

    $message = $twilio->messages
      ->create("whatsapp:+6285727648461", // to
        array(
          "from" => "whatsapp:+14155238886",
          "body" => "Anjeng LOOOO"
        )
      );

    print($message->sid);
?>