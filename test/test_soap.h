#ifndef TEST_SOAP_H
#define TEST_SOAP_H

#include "test.h"
#include <algorithm>
#include <soap/wsdl_parser.h>
#include <soap/class_generator.h>
#include <core/string_helper.h>
#include <iostream>

void test_soap() {

    tooska::html::html_document _html;
       std::string wsdl_text = R"(<?xml version="1.0" encoding="utf-8"?>
<wsdl:definitions xmlns:schema="http://sayanCard/merchant/definitions" xmlns:soap="http://schemas.xmlsoap.org/wsdl/soap/" targetNamespace="http://sayanCard/merchant/definitions" xmlns:wsdl="http://schemas.xmlsoap.org/wsdl/">
  <wsdl:types>
    <schema xmlns:tns="http://sayanCard/merchant/definitions" attributeFormDefault="qualified" elementFormDefault="qualified" targetNamespace="http://sayanCard/merchant/definitions" xmlns="http://www.w3.org/2001/XMLSchema">
      <element name="getPaymentTicketRequest">
        <complexType>
          <sequence maxOccurs="1">
            <element minOccurs="1" name="merchantId" type="string" />
            <element minOccurs="1" name="wsp1" type="string" />
            <element minOccurs="1" name="wsp2" type="string" />
            <element minOccurs="1" name="amount" type="string" />
            <element minOccurs="1" name="paymentId" type="string" />
            <element minOccurs="0" name="customerId" type="string" />
          </sequence>
        </complexType>
      </element>
      <element name="getPaymentTicketResponse">
        <complexType>
          <sequence>
            <element minOccurs="1" name="paymentTicket" type="string" />
            <element minOccurs="0" name="errorOccur" type="tns:errorOccur" />
          </sequence>
        </complexType>
      </element>
      <element name="verifyRequest">
        <complexType>
          <sequence maxOccurs="1">
            <element minOccurs="1" name="merchantId" type="string" />
            <element minOccurs="1" name="wsp1" type="string" />
            <element minOccurs="1" name="wsp2" type="string" />
            <element minOccurs="1" name="paymentTicket" type="string" />
          </sequence>
        </complexType>
      </element>
      <element name="verifyResponse">
        <complexType>
          <sequence>
            <element minOccurs="1" name="resultCode" type="string" />
            <element minOccurs="1" name="paymentId" type="string" />
          </sequence>
        </complexType>
      </element>
      <complexType name="errorOccur">
        <sequence maxOccurs="1">
          <element name="errorCode" type="int" />
          <element name="errorDescription" type="string" />
        </sequence>
      </complexType>
      <element name="errorOccur" type="tns:errorOccur" />
    </schema>
  </wsdl:types>
  <wsdl:message name="getPaymentTicketResponse">
    <wsdl:part name="getPaymentTicketResponse" element="schema:getPaymentTicketResponse" />
  </wsdl:message>
  <wsdl:message name="getPaymentTicketRequest">
    <wsdl:part name="getPaymentTicketRequest" element="schema:getPaymentTicketRequest" />
  </wsdl:message>
  <wsdl:message name="verifyResponse">
    <wsdl:part name="verifyResponse" element="schema:verifyResponse" />
  </wsdl:message>
  <wsdl:message name="verifyRequest">
    <wsdl:part name="verifyRequest" element="schema:verifyRequest" />
  </wsdl:message>
  <wsdl:portType name="merchant">
    <wsdl:operation name="getPaymentTicket">
      <wsdl:input name="getPaymentTicketRequest" message="schema:getPaymentTicketRequest" />
      <wsdl:output name="getPaymentTicketResponse" message="schema:getPaymentTicketResponse" />
    </wsdl:operation>
    <wsdl:operation name="verify">
      <wsdl:input name="verifyRequest" message="schema:verifyRequest" />
      <wsdl:output name="verifyResponse" message="schema:verifyResponse" />
    </wsdl:operation>
  </wsdl:portType>
  <wsdl:binding name="merchantBinding" type="schema:merchant">
    <soap:binding transport="http://schemas.xmlsoap.org/soap/http" />
    <wsdl:operation name="getPaymentTicket">
      <soap:operation soapAction="" />
      <wsdl:input name="getPaymentTicketRequest">
        <soap:body use="literal" />
      </wsdl:input>
      <wsdl:output name="getPaymentTicketResponse">
        <soap:body use="literal" />
      </wsdl:output>
    </wsdl:operation>
    <wsdl:operation name="verify">
      <soap:operation soapAction="" />
      <wsdl:input name="verifyRequest">
        <soap:body use="literal" />
      </wsdl:input>
      <wsdl:output name="verifyResponse">
        <soap:body use="literal" />
      </wsdl:output>
    </wsdl:operation>
  </wsdl:binding>
  <wsdl:service name="merchant">
    <wsdl:port name="merchantBindingPort" binding="schema:merchantBinding">
      <soap:address location="https://sayan.shaparak.ir/ws/payment/merchant.wsdl" />
    </wsdl:port>
  </wsdl:service>
</wsdl:definitions>
)";

//    tooska::core::string_helper::replace(wsdl_text, "wsdl:", "");
    tooska::soap::wsdl_parser wp;
    wp.set_content(wsdl_text);
    std::cout << "wsdl version " << wp.version_str() << " parsed!" << std::endl;
    tooska::soap::class_generator cl(&wp);
    cl.generate();

}

#endif // TEST_SOAP_H
