#include <pgmspace.h>
#define SECRET
#define THINGNAME "test_build_3"
const char WIFI_SSID[] = "Surya";
const char WIFI_PASSWORD[] = "11111111"; 
const char AWS_IOT_ENDPOINT[] = "agv0ibwkjrswz-ats.iot.ap-south-1.amazonaws.com";
 
// Amazon Root CA 1
static const char AWS_CERT_CA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----
)EOF";
 
// Device Certificate                                               //change this
static const char AWS_CERT_CRT[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
MIIDWTCCAkGgAwIBAgIUCVhJHuaWeaki7Paj2EBmcyN5A64wDQYJKoZIhvcNAQEL
BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g
SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTI0MDgyNDIxMzY1
NVoXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0
ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAO7adhb8/H8iPRt9Wkfw
pnDWlyfKan+oAMdur+u7EQc9li7Tq/0Vlcg0SSP09xAFlyaTq4DhR3bAqu55i67y
Uds/rOSnhwZKzJ48z6lYfKQdwpsdJ3l6O+4mTdty4Bo2GNF/UoiFRYS6WDpszgPt
3vSLZJ4imRBGAL/MHRUZAPZpVMPLAbIBgpTS4G4IYHavqmK5XXfh8xUg9WCNfP6E
6yivJwdGWltD6uWHf9ThH9MRo6YT6JzJH6Z4dY4a/cj6C1hBVbIG+KcUXLRMQ70a
o1XfRywG7YODe0OHEQYdEpKiL5c40JDFg5jay8HuAxzmRHLXBi9QFMGjSlY+nOr4
Y7cCAwEAAaNgMF4wHwYDVR0jBBgwFoAU5l3+cZFe+662dFGiXnNPrVpoLZQwHQYD
VR0OBBYEFJjBD3WyU7724bZdVx6slifEKBKfMAwGA1UdEwEB/wQCMAAwDgYDVR0P
AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQBzZKMwGgY29OsQ121nrbIDCk3N
Yw3gN3ZbA3uGkEIMmhfuk8X0MA2CpT1orCNdoljs2i/0scm+Pf+h3Tpv+tGTyVMy
bA7NHPb/Z4/BsUef0AfoRTFjFLgvWVs19FE/Tu+BHDteqUKiVprjEYE/dlDdpeBj
wRFFYzwHf1ZZr+aCKFus819ldHeEfXpk/wLSZhMrEFaATII2/Z1BjdJmaHg9D8dj
R6faPmC1i4q6S51dvlXDB+v1rtHqV0ZeGlR5PWYsCK217gLFDPrDLs7tNTcPCRBv
QILczVydwq0iyLX5s1k7d7CL65tYPQ7etbz9NKKooB4dRzOS+xfBHEJyrQAR
-----END CERTIFICATE-----
)KEY";
 
// Device Private Key                                               //change this
static const char AWS_CERT_PRIVATE[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
MIIEowIBAAKCAQEA7tp2Fvz8fyI9G31aR/CmcNaXJ8pqf6gAx26v67sRBz2WLtOr
/RWVyDRJI/T3EAWXJpOrgOFHdsCq7nmLrvJR2z+s5KeHBkrMnjzPqVh8pB3Cmx0n
eXo77iZN23LgGjYY0X9SiIVFhLpYOmzOA+3e9ItkniKZEEYAv8wdFRkA9mlUw8sB
sgGClNLgbghgdq+qYrldd+HzFSD1YI18/oTrKK8nB0ZaW0Pq5Yd/1OEf0xGjphPo
nMkfpnh1jhr9yPoLWEFVsgb4pxRctExDvRqjVd9HLAbtg4N7Q4cRBh0SkqIvlzjQ
kMWDmNrLwe4DHOZEctcGL1AUwaNKVj6c6vhjtwIDAQABAoIBAFBzMLdJetpvc9mg
fRoiCk2TWdJDMV/R/IEv3P0vQusHaWBYV2OlM4/9XG1KAzVYTLLnpiqAtotfFbPB
KLVCVSPd7KQPcUFDTGw321IUxdaZV4TbawJVk34BVNQHe0gY1H8rvWbSTLoJ8dGr
+DAGnMQNd1R0Hs4GZhYz78+9Xj+gUB6bT+DyBTBBPRBWGtS1az1O7P6xk2ZJrgju
agrbm0fkMdCtDKZdCpzSsygOpKQLrPkwgbUv8XRF1IeSpJ4HJLMwHY3B7ZU0Vhz9
c6QzBOOVvX6tWagYWdrxoGwnyM0dwSWxUVDXeIv9sxpEVrD0Nam5pOc/jKYnhvrw
1yo0dyECgYEA+sNzVk0gr24C6HM/dv6ysjiIMF7rXJcwOf1zJV5K6d+bfHj9x/XI
tL/m8mZtJTyzih6EhVwjJmI7FwcRgnBWJj0cmkl7Pioaqmh8qpiOnT/mLLc32cNw
VRf1AsZvhCoanP3Et5Jcl2nPFbiC0w76dJGW7wMGaCDN6eZFBGMAxlkCgYEA89dX
PxJgNWa1dwuQcUmYiXKyY+8o5WblPzIQZ1ZPIkA+55IrkCdA44F8djRsFaXJ08vU
AqxeXTu2XeKMvQyQePfsqW8XvUgXphSQ8SXExMM1ALSPtJDNzCjizcUdXevCQJDv
hzaUDHQvslN2cwCksJ06cmkfTH1X8yN1LQ7TWI8CgYEA3Bp6PiHsso7pVobyCcx9
pRkh0PM/u0GpPv1L+FzPfICcxaCdgMonpR9b4yAsZSbmoDExOK0q3SITo568q7VW
qLGzTWl6F5J1XWXhJwxJAZV4v38CMs3s54Pjts/eSi96tJm59TcutmhVMEeH7SGU
jITN6nTJRtSkaM2JftQ3deECgYBq6c1AQ09ZurnwA2sGsQ0nntmmxZL52n7DkbDt
jkNOMjsij813/C4QUpL+xQdrCnEO4z0HGwqY+HiCe7XXoi2qTJJAzAvtmzF7SWMv
yK6Y0zpnH8QumJsTXA3tyPKSXq+iXaoYcA7D0yGin8O8stiC871PstXdVMv+OFrF
Mc3q8wKBgCFzrafrN2GGnlRE65ZWZEPDeNp1AqtsuRdQOkGiPGF8STra+lD90XLA
RHZiqU9GdspdgXDbvCtTHQmPscnTLmSV9ttG5F38cb247EX/cVwa9hxjCLgDghi2
owvx76lYie6LhBZHgFyMPND2OrdGHCdvI4Ucw2eR20yR3N+voU6Y
-----END RSA PRIVATE KEY-----
)KEY";