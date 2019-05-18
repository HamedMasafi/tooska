# Any parser

Any parser is a simple and lightweight parsing library that can parse documents of types _html_, _css_ and _json_ (xml is comming soon).

## More documents
* [JSON](doc/json.md)
* [HTML](doc/html.md)
* [CSS](doc/css.md)

## License
LGPL v2

## Sample usage
```cpp
    auto html_text = R"~(<!DOCTYPE HTML>
                     <html>
                     <head>
                     <meta name="qrichtext" content="1" />
                     <style type="text/css">
                     p, li { white-space: pre-wrap; }
                     b { color: "red" }
                     </style>
                     </head>
                     <body style=" font-family:'Noto Sans'; font-size:10pt; font-weight:400; font-style:normal;">
                     <p style=" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;">dfg</p>
                     <img src="image.png" />
                     <p id="p1" class="par">
                     <b>Sample</b> paragraph
                     <img src="image.png" />
                     </p>
                     </body>
                     </html>)~";
    html_parser html;
    html.set_text(html_text);
    auto b = html.query("body .p1 b").at(0);
    b->add_class("text-danger");
    b->set_attr("dir", "rt");
```