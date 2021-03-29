cmake_minimum_required(VERSION 3.0.0)
project(sipsdk VERSION 0.1.0)

include(CTest)
enable_testing()
add_definitions( -DSIPSDK_STATIC)
#source files directory
add_library(${PROJECT_NAME}
"sipsdk/Ack.cpp"
"sipsdk/Bye.cpp"
"sipsdk/ContentLength.cpp"
"sipsdk/Expires.cpp"
"sipsdk/Forwards.cpp"
"sipsdk/From.cpp"
"sipsdk/Invite.cpp"
"sipsdk/MediaAttribute.cpp"
"sipsdk/MediaCodec.cpp"
"sipsdk/MediaDescription.cpp"
"sipsdk/Options.cpp"
"sipsdk/Register.cpp"
"sipsdk/Request.cpp"
"sipsdk/SdpAttributes.cpp"
"sipsdk/SdpConnection.cpp"
"sipsdk/SdpHeader.cpp"
"sipsdk/SdpOrigin.cpp"
"sipsdk/SdpVersion.cpp"
"sipsdk/Sequence.cpp"
"sipsdk/SessionDescription.cpp"
"sipsdk/Sip.cpp"
"sipsdk/SipException.cpp"
"sipsdk/SipHeader.cpp"
"sipsdk/SipResponse.cpp"
"sipsdk/SipUri.cpp"
"sipsdk/Subscribe.cpp"
"sipsdk/To.cpp"
"sipsdk/UriBase.cpp"
"sipsdk/UserAgent.cpp"
"sipsdk/Via.cpp"
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
