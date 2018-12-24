const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <title>IOT Project</title>
</head>
<body>
    <center>
        <div>
            <h1>IOT based Agricultural practices.</h1>
        </div>
        <div>
            <table border="5" cellpadding=4 cellspacing=4 width=70%>
                <tr>
                    <th width="80%">Measurement :</th>
                    <th width="20%">Value</th>
                </tr>
                <tr>
                    <td align=center>Soil Moisture Content :</td>
                    <td align=center>@@moistureContent@@</td>
                </tr>
                <tr>
                    <td align=center>Water level in tank :</td>
                    <td align=center>@@waterLevel@@</td>
                </tr>
                <tr>
                    <td align=center>Press to switch ON water supply in soil :</td>
                    <td align=center><input type="submit" value="ON1"></td>
                </tr>
                <tr>
                    <td align=center>Press to switch OFF water supply in soil :</td>
                    <td align=center><input type="submit" value="OFF1"></td>
                </tr>
                <tr>
                    <td align=center>Press to switch ON water supply in tank :</td>
                    <td align=center><input type="submit" value="ON2"></td>
                </tr>
                <tr>
                    <td align=center>Press to switch OFF water supply in tank :</td>
                    <td align=center><input type="submit" value="OFF2"></td>
                </tr>
            </table>
        </div>
       
    </center>

</body>
</html>
)=====";
