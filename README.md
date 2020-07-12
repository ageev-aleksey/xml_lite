# xml to txt service [![Build Status](https://travis-ci.com/ageev-aleksey/xml_lite.svg?branch=master)](https://travis-ci.com/ageev-aleksey/xml_lite)

## Предназначение

Демон запускаемый через systemd, который выполняет проверку наличие файла test.xml в директории /data_input, 
если файл там есть, то выполняет преобразование в текстовый формат. Данные в текстовом формате записываются по пути /data_output/out.txt, 
а файл test.xml переносится в папку /to_delete

**Пример**
 - /input_data/test.xml
 ````xml
<?xml version = "1.0" encoding = "utf-8"?>
    <Table name="param_text" valuetype="data" type="text/xml" timestamp="2019-12-31 23:59:02.047">
        <param_text>
            <name>Алексеев Иван Петрович</name>
            <date>1976-01-01</date>
            <hours-worked>25</hours-worked>
            <car-true>YES</car-true>
        </param_text>
        <param_text>
            <name>Петров Сергей Иванович</name>
            <date>1996-01-01</date>
            <hours-worked>8</hours-worked>
            <car-true>YES</car-true>
        </param_text>
        <param_text>
            <name>Колесников Иван Сергеевич</name>
            <date>2002-11-01</date>
            <hours-worked>8</hours-worked>
            <car-true>YES</car-true>
        </param_text>
        <param_text>
            <name>Осипов Алексей Иванович</name>
            <date>2002-11-21</date>
            <hours-worked>16</hours-worked>
            <car-true>YES</car-true>
        </param_text>
    </Table>
 ````
 - /output_data/out.txt
````text
Алексеев Иван Петрович
1976-01-01
25
YES

Петров Сергей Иванович
1996-01-01
8
YES

Колесников Иван Сергеевич
2002-11-01
8
YES

Осипов Алексей Иванович
2002-11-21
16
YES

````
 - /input_data/test.xml -> /to_delete/test.xml.0001
## Установка

````shell script
mkdir build
cd build
cmake ..
cmake --build . --target install
cd .. 
mkdir /opt/xml_to_txt_service
mv ./bin/app /opt/xml_to_txt_service/app
cp xml_to_txt.service /etc/systemd/system/xml_to_txt.service
systemctl daemon-reload
systemctl start xml_to_txt
````