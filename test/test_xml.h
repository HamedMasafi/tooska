#ifndef TEST_XML_H
#define TEST_XML_H

#include "test.h"
#include <algorithm>
#include <xml/xml_document.h>
#include <xml/xml_node.h>

void test_xml() {

    tooska::xml::xml_document _xml;
    auto xml_text = R"~(
<note>
  <date>2015-09-01</date>
  <hour>08:30</hour>
  <to>Tove</to>
  <from>Jani</from>
  <body>Don't forget me this weekend!</body>
</note>)~";

    _xml.set_text(xml_text);

    auto note = _xml.find("note").first();
    ASSERT(note);

    ASSERT(note->find("to").first())

}

#endif // TEST_XML_H
