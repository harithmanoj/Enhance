<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile>
  <compound kind="file">
    <name>common.enh.h</name>
    <path>F:/source/Enhance/src/Header/</path>
    <filename>common_8enh_8h.html</filename>
    <includes id="framework_8enh_8h" name="framework.enh.h" local="yes" imported="no">framework.enh.h</includes>
    <includes id="logger_8enh_8h" name="logger.enh.h" local="yes" imported="no">logger.enh.h</includes>
    <class kind="class">enh::error_base</class>
    <namespace>enh</namespace>
    <member kind="define">
      <type>#define</type>
      <name>LIB_ERROR_FLAG_LOG</name>
      <anchorfile>common_8enh_8h.html</anchorfile>
      <anchor>ac1173d82ebbeb190649ef1a93fafd95c</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ERROR_FLAG_LOG</name>
      <anchorfile>common_8enh_8h.html</anchorfile>
      <anchor>afa6247e0a8d6ff59ab3bffd8ff71c64e</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>LIB_ERROR_FLAG_LOGP</name>
      <anchorfile>common_8enh_8h.html</anchorfile>
      <anchor>a15482f7ba898ea83b2b9707774404fe7</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ERROR_FLAG_LOGP</name>
      <anchorfile>common_8enh_8h.html</anchorfile>
      <anchor>a053e0da58b8b08ea7ec5d443538a92df</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>tristate</name>
      <anchorfile>namespaceenh.html</anchorfile>
      <anchor>a61067ccf704a6ec6d8a407f8394b004b</anchor>
      <arglist></arglist>
      <enumvalue file="namespaceenh.html" anchor="a61067ccf704a6ec6d8a407f8394b004ba45802158e78dd9584161629098018fe8">GOOD</enumvalue>
      <enumvalue file="namespaceenh.html" anchor="a61067ccf704a6ec6d8a407f8394b004babb1ca97ec761fc37101737ba0aa2e7c5">ERROR</enumvalue>
      <enumvalue file="namespaceenh.html" anchor="a61067ccf704a6ec6d8a407f8394b004ba0205fe53d2d6958c15ab0aaee27b060f">PREV_ERR</enumvalue>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator!</name>
      <anchorfile>namespaceenh.html</anchorfile>
      <anchor>a812420b64dc76bb983d6b627c9e433a2</anchor>
      <arglist>(tristate e) noexcept</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>checkField</name>
      <anchorfile>namespaceenh.html</anchorfile>
      <anchor>a5084827e591e0425d76b9752ae751794</anchor>
      <arglist>(enumT in, enumT field) noexcept</arglist>
    </member>
    <member kind="variable">
      <type>constexpr short</type>
      <name>signum</name>
      <anchorfile>namespaceenh.html</anchorfile>
      <anchor>a1373aa9e1df59df05a38e668bd25402b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr unsigned long long</type>
      <name>inclusive_ratio</name>
      <anchorfile>namespaceenh.html</anchorfile>
      <anchor>a3749434e1f10c025f00032a51f2aba25</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>counter.enh.h</name>
    <path>F:/source/Enhance/src/Header/</path>
    <filename>counter_8enh_8h.html</filename>
    <includes id="framework_8enh_8h" name="framework.enh.h" local="yes" imported="no">framework.enh.h</includes>
    <class kind="class">enh::counter</class>
    <namespace>enh</namespace>
    <member kind="function">
      <type>counter</type>
      <name>max</name>
      <anchorfile>namespaceenh.html</anchorfile>
      <anchor>a5f461456cf52f5d925004b085dd84761</anchor>
      <arglist>(const counter a, const counter b) noexcept</arglist>
    </member>
    <member kind="function">
      <type>counter</type>
      <name>min</name>
      <anchorfile>namespaceenh.html</anchorfile>
      <anchor>af17a502dc7630b917abc0c438cbfb18c</anchor>
      <arglist>(const counter a, const counter b) noexcept</arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>namespaceenh.html</anchorfile>
      <anchor>a51d3bfd96daf7772870f6390df3a1d00</anchor>
      <arglist>(std::ostream &amp;out, counter ct) noexcept</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>framework.enh.h</name>
    <path>F:/source/Enhance/src/Header/</path>
    <filename>framework_8enh_8h.html</filename>
    <class kind="class">enh::version_info</class>
    <namespace>enh</namespace>
    <member kind="define">
      <type>#define</type>
      <name>VERSION_INFO_BETA</name>
      <anchorfile>framework_8enh_8h.html</anchorfile>
      <anchor>a1c3459a0275725d30597ead5e462101b</anchor>
      <arglist>(mj, mn, re, bl)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VERSION_INFO_FIN</name>
      <anchorfile>framework_8enh_8h.html</anchorfile>
      <anchor>a76f8696dffccd48706b74844e9de764c</anchor>
      <arglist>(mj, mn, re, bl)</arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>rel_type</name>
      <anchorfile>namespaceenh.html</anchorfile>
      <anchor>a0b0e871be4713899208ceba5d9b14172</anchor>
      <arglist></arglist>
      <enumvalue file="namespaceenh.html" anchor="a0b0e871be4713899208ceba5d9b14172a36b84f8e3fba5bf993e3ba352d62d146">BETA</enumvalue>
      <enumvalue file="namespaceenh.html" anchor="a0b0e871be4713899208ceba5d9b14172a7d649ef069df9885e382417c79f3d5cd">RELEASE</enumvalue>
    </member>
    <member kind="variable">
      <type>constexpr version_info</type>
      <name>enhance_version</name>
      <anchorfile>namespaceenh.html</anchorfile>
      <anchor>a0dbd8c46a7fbad18f9f73298a9b9b88a</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>logger.enh.h</name>
    <path>F:/source/Enhance/src/Header/</path>
    <filename>logger_8enh_8h.html</filename>
    <includes id="framework_8enh_8h" name="framework.enh.h" local="yes" imported="no">framework.enh.h</includes>
    <namespace>debug</namespace>
    <member kind="define">
      <type>#define</type>
      <name>REPLACE</name>
      <anchorfile>logger_8enh_8h.html</anchorfile>
      <anchor>a5b7ee3cb6b594766892973048166ab2b</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>REPLACE_AS</name>
      <anchorfile>logger_8enh_8h.html</anchorfile>
      <anchor>a87c3774199834ad3251dc50b70b0b259</anchor>
      <arglist>(x, y)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>NDBG_REPLACE</name>
      <anchorfile>logger_8enh_8h.html</anchorfile>
      <anchor>a0e7c10ba735b78c5e07c86147957a897</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>NDBG_REPLACE_AS</name>
      <anchorfile>logger_8enh_8h.html</anchorfile>
      <anchor>a268e03a698aa12b7bd13fce479598af9</anchor>
      <arglist>(x, y)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>O5_REPLACE</name>
      <anchorfile>logger_8enh_8h.html</anchorfile>
      <anchor>a756707d42e7a59fb47c6c4eca988e34a</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>O5_REPLACE_AS</name>
      <anchorfile>logger_8enh_8h.html</anchorfile>
      <anchor>a17f001562174d753d44affd97a9282c3</anchor>
      <arglist>(x, y)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>O4_REPLACE</name>
      <anchorfile>logger_8enh_8h.html</anchorfile>
      <anchor>ab11d9b7d2947b4b05eaa476be2335446</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>O4_REPLACE_AS</name>
      <anchorfile>logger_8enh_8h.html</anchorfile>
      <anchor>a5a9d1c8a9cc4cca5b4a6ba7f19eb3906</anchor>
      <arglist>(x, y)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>O3_REPLACE</name>
      <anchorfile>logger_8enh_8h.html</anchorfile>
      <anchor>a31f7d515616bc1ca3e025a44696e221e</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>O3_REPLACE_AS</name>
      <anchorfile>logger_8enh_8h.html</anchorfile>
      <anchor>ae032ff95ea26d0d14b874f41bf83bae8</anchor>
      <arglist>(x, y)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>O2_REPLACE</name>
      <anchorfile>logger_8enh_8h.html</anchorfile>
      <anchor>a10baa031fc20469494e078bef16ded0d</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>O2_REPLACE_AS</name>
      <anchorfile>logger_8enh_8h.html</anchorfile>
      <anchor>aa2030ca3fcdb9a6aec4b3080b6c794e4</anchor>
      <arglist>(x, y)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>O1_REPLACE</name>
      <anchorfile>logger_8enh_8h.html</anchorfile>
      <anchor>a58dbe81c803a07901201746e6ab280ec</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>O1_REPLACE_AS</name>
      <anchorfile>logger_8enh_8h.html</anchorfile>
      <anchor>a239ff35cb169eeff1787c9d6ea4aa69c</anchor>
      <arglist>(x, y)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>LIB_REPLACE</name>
      <anchorfile>logger_8enh_8h.html</anchorfile>
      <anchor>ae60d43340c9acbc8de39c596865ae5b5</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>LIB_REPLACE_AS</name>
      <anchorfile>logger_8enh_8h.html</anchorfile>
      <anchor>a9d113e8863d81c43bed558aa85fb576f</anchor>
      <arglist>(x, y)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>O5_LIB_REPLACE</name>
      <anchorfile>logger_8enh_8h.html</anchorfile>
      <anchor>a28ff2434df93a0ef459dc6975c087d38</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>O4_LIB_REPLACE</name>
      <anchorfile>logger_8enh_8h.html</anchorfile>
      <anchor>ae37448d5fb9e49211a41f4052ae04c00</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>O3_LIB_REPLACE</name>
      <anchorfile>logger_8enh_8h.html</anchorfile>
      <anchor>aaaec7a3b6ab22dcd9597a425c366f777</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>O2_LIB_REPLACE</name>
      <anchorfile>logger_8enh_8h.html</anchorfile>
      <anchor>a1e74e1afb369f904ac6a2ec448eee47f</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>O1_LIB_REPLACE</name>
      <anchorfile>logger_8enh_8h.html</anchorfile>
      <anchor>aa8bf495e1f2492f86503ee95c790230e</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>O5_LIB_REPLACE_AS</name>
      <anchorfile>logger_8enh_8h.html</anchorfile>
      <anchor>abbeaaa0f10e613485aebea69fd8fcbb0</anchor>
      <arglist>(x, y)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>O4_LIB_REPLACE_AS</name>
      <anchorfile>logger_8enh_8h.html</anchorfile>
      <anchor>a5cd1f537b3f5f1b2064d4ad5f5b0b3ea</anchor>
      <arglist>(x, y)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>O3_LIB_REPLACE_AS</name>
      <anchorfile>logger_8enh_8h.html</anchorfile>
      <anchor>a5e4b66f8fb6585edcbc9f2887f1fe308</anchor>
      <arglist>(x, y)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>O2_LIB_REPLACE_AS</name>
      <anchorfile>logger_8enh_8h.html</anchorfile>
      <anchor>a6b28fe8db2d10a6037aab65dff514631</anchor>
      <arglist>(x, y)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>O1_LIB_REPLACE_AS</name>
      <anchorfile>logger_8enh_8h.html</anchorfile>
      <anchor>a4ef4f38fae577b715a34b734fc773546</anchor>
      <arglist>(x, y)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>INFO_FOR_LOG</name>
      <anchorfile>logger_8enh_8h.html</anchorfile>
      <anchor>ab5de78a447c8c3a83ab83f65044af308</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>LOG_LINE</name>
      <anchorfile>logger_8enh_8h.html</anchorfile>
      <anchor>a9917792a9ae6fb8263dd825556b1adc1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>LOG_DESC</name>
      <anchorfile>logger_8enh_8h.html</anchorfile>
      <anchor>acfc65a19f5e85486ddc830b77d4a2398</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>LOG_VAL</name>
      <anchorfile>logger_8enh_8h.html</anchorfile>
      <anchor>af329f089bb4b5fed246cd36aa698b107</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>LIB_LOG_LINE</name>
      <anchorfile>logger_8enh_8h.html</anchorfile>
      <anchor>ad825cc3fbe076b63a32289e85099aaa3</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>LIB_LOG_DESC</name>
      <anchorfile>logger_8enh_8h.html</anchorfile>
      <anchor>a221a201e3be8bc19b8ecb9337295ebc2</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>LIB_LOG_VAL</name>
      <anchorfile>logger_8enh_8h.html</anchorfile>
      <anchor>a01f54130cf98192961ae779e165cb495</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>O5_LOG_LINE</name>
      <anchorfile>logger_8enh_8h.html</anchorfile>
      <anchor>ac02cc8c08e4291c1b5a59a67961878b3</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>O5_LOG_DESC</name>
      <anchorfile>logger_8enh_8h.html</anchorfile>
      <anchor>a7c01f83d6366189aa63df1d7d886b127</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>O5_LOG_VAL</name>
      <anchorfile>logger_8enh_8h.html</anchorfile>
      <anchor>a061e35750a2901bda0bd04d882d8e165</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>O4_LOG_LINE</name>
      <anchorfile>logger_8enh_8h.html</anchorfile>
      <anchor>acdfeec0431870da5f94661730c27dcc0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>O4_LOG_DESC</name>
      <anchorfile>logger_8enh_8h.html</anchorfile>
      <anchor>a7602cf093e7ab12ae893d67e95aa4acc</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>O4_LOG_VAL</name>
      <anchorfile>logger_8enh_8h.html</anchorfile>
      <anchor>a08e43fe50a95f6ada56619ee2cf2c5db</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>O3_LOG_LINE</name>
      <anchorfile>logger_8enh_8h.html</anchorfile>
      <anchor>aa5c6c52e960848e2c453f4abb65be41a</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>O3_LOG_DESC</name>
      <anchorfile>logger_8enh_8h.html</anchorfile>
      <anchor>a48ea2d0eeec50fe06ac59a1e725cd5df</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>O3_LOG_VAL</name>
      <anchorfile>logger_8enh_8h.html</anchorfile>
      <anchor>abdae39696a098bacbbed4402635c3040</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>O2_LOG_LINE</name>
      <anchorfile>logger_8enh_8h.html</anchorfile>
      <anchor>af2632638f1e8bacdb0721bd4ef8a101f</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>O2_LOG_DESC</name>
      <anchorfile>logger_8enh_8h.html</anchorfile>
      <anchor>a8a78f43caa009e43cbe7f1f694b374b1</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>O2_LOG_VAL</name>
      <anchorfile>logger_8enh_8h.html</anchorfile>
      <anchor>aaa92014d2182c8967599fac45300dc77</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>O1_LOG_LINE</name>
      <anchorfile>logger_8enh_8h.html</anchorfile>
      <anchor>a1dc2aff52221a4397a692d11d128005e</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>O1_LOG_DESC</name>
      <anchorfile>logger_8enh_8h.html</anchorfile>
      <anchor>a4909bb41bd9f6c6f54f3b9e8ff57f00f</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>O1_LOG_VAL</name>
      <anchorfile>logger_8enh_8h.html</anchorfile>
      <anchor>a2d6917c4dd1415d769c90b4f8becc831</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>O5_LIB_LOG_LINE</name>
      <anchorfile>logger_8enh_8h.html</anchorfile>
      <anchor>a532b51862bc7f284b99fbec1a5d23bba</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>O5_LIB_LOG_DESC</name>
      <anchorfile>logger_8enh_8h.html</anchorfile>
      <anchor>afffd4d7debfe4a4de0cb14931fac6327</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>O5_LIB_LOG_VAL</name>
      <anchorfile>logger_8enh_8h.html</anchorfile>
      <anchor>a91077974f91fb93cac62e690321fdd9e</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>O4_LIB_LOG_LINE</name>
      <anchorfile>logger_8enh_8h.html</anchorfile>
      <anchor>a2ab7b68ef60fa4817e3bd32b735202c0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>O4_LIB_LOG_DESC</name>
      <anchorfile>logger_8enh_8h.html</anchorfile>
      <anchor>a247cee3b27336089f4e32f5270277f60</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>O4_LIB_LOG_VAL</name>
      <anchorfile>logger_8enh_8h.html</anchorfile>
      <anchor>a7763231ccc225946dbe8c6db06998136</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>O3_LIB_LOG_LINE</name>
      <anchorfile>logger_8enh_8h.html</anchorfile>
      <anchor>a6d274eca98e6d105175155926d633e71</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>O3_LIB_LOG_DESC</name>
      <anchorfile>logger_8enh_8h.html</anchorfile>
      <anchor>aef6224931690de35b8c5d4a756a4ca6d</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>O3_LIB_LOG_VAL</name>
      <anchorfile>logger_8enh_8h.html</anchorfile>
      <anchor>aa4c86acdf4a8c449f7ea82865b332425</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>O2_LIB_LOG_LINE</name>
      <anchorfile>logger_8enh_8h.html</anchorfile>
      <anchor>a37c359f03c11ca323f85f3d8914de295</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>O2_LIB_LOG_DESC</name>
      <anchorfile>logger_8enh_8h.html</anchorfile>
      <anchor>a36ee04658ea5101409bbd0ea1f6830d0</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>O2_LIB_LOG_VAL</name>
      <anchorfile>logger_8enh_8h.html</anchorfile>
      <anchor>a66677c61970c37d3a286ff51b8e377aa</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>O1_LIB_LOG_LINE</name>
      <anchorfile>logger_8enh_8h.html</anchorfile>
      <anchor>a55cb0e7a838cf0ce5d14a0897d28e987</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>O1_LIB_LOG_DESC</name>
      <anchorfile>logger_8enh_8h.html</anchorfile>
      <anchor>a21da0d161362a81408a9bf1f2b119e0d</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>O1_LIB_LOG_VAL</name>
      <anchorfile>logger_8enh_8h.html</anchorfile>
      <anchor>acf57b1ae2cbb87643ea9748fd407e985</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="function">
      <type>std::filesystem::path</type>
      <name>getFile</name>
      <anchorfile>namespacedebug.html</anchorfile>
      <anchor>a89c8e27f837f3ee4e4fce0b46ae82ccf</anchor>
      <arglist>(std::thread::id id, std::string function)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Log</name>
      <anchorfile>namespacedebug.html</anchorfile>
      <anchor>a24f177f77e5c8af3922ada72aea089ac</anchor>
      <arglist>(std::string lg, std::string function)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Log</name>
      <anchorfile>namespacedebug.html</anchorfile>
      <anchor>a734ce3feb2187ac6495262f52f7b3753</anchor>
      <arglist>(std::string file, std::string function, unsigned long line)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Log</name>
      <anchorfile>namespacedebug.html</anchorfile>
      <anchor>ae5935b08444a6013a0f16fd8a0e2900d</anchor>
      <arglist>(std::string file, std::string function, unsigned long line, std::string descr)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Log</name>
      <anchorfile>namespacedebug.html</anchorfile>
      <anchor>a717f2ef93984eb5de567d96bc78ede21</anchor>
      <arglist>(std::string file, std::string function, unsigned long line, std::string var, const T &amp;val)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>queued_process.enh.h</name>
    <path>F:/source/Enhance/src/Header/</path>
    <filename>queued__process_8enh_8h.html</filename>
    <includes id="logger_8enh_8h" name="logger.enh.h" local="yes" imported="no">logger.enh.h</includes>
    <includes id="common_8enh_8h" name="common.enh.h" local="yes" imported="no">common.enh.h</includes>
    <class kind="struct">enh::gen_instruct</class>
    <class kind="struct">enh::quad_instruct</class>
    <class kind="class">enh::blank_t</class>
    <class kind="class">enh::queued_process</class>
    <namespace>enh</namespace>
  </compound>
  <compound kind="file">
    <name>timer.enh.h</name>
    <path>F:/source/Enhance/src/Header/</path>
    <filename>timer_8enh_8h.html</filename>
    <includes id="logger_8enh_8h" name="logger.enh.h" local="yes" imported="no">logger.enh.h</includes>
    <class kind="class">enh::timer</class>
    <namespace>enh</namespace>
    <member kind="typedef">
      <type>std::chrono::high_resolution_clock</type>
      <name>high_res</name>
      <anchorfile>namespaceenh.html</anchorfile>
      <anchor>aa3b22608dd9a6d477676c2d5580f09b9</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>decltype(high_res::now())</type>
      <name>time_pt</name>
      <anchorfile>namespaceenh.html</anchorfile>
      <anchor>a8f5724afac4fbbae9067dbc98fa4e7d8</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>timer&lt; 50, std::chrono::nanoseconds &gt;</type>
      <name>nanos</name>
      <anchorfile>namespaceenh.html</anchorfile>
      <anchor>a40787cb24d744d28ea8b7105af612f81</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>timer&lt; 50, std::chrono::microseconds &gt;</type>
      <name>micros</name>
      <anchorfile>namespaceenh.html</anchorfile>
      <anchor>a4161dbe2decf77ed6da3d93d5ed14c9d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>timer&lt; period, std::chrono::milliseconds &gt;</type>
      <name>millis</name>
      <anchorfile>namespaceenh.html</anchorfile>
      <anchor>abaa97670f060ac3bf5704a6c3350e8bb</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>timer&lt; period, std::chrono::seconds &gt;</type>
      <name>seconds</name>
      <anchorfile>namespaceenh.html</anchorfile>
      <anchor>a0e90f21da57b74c795abcad09d29622a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>timer&lt; period, std::chrono::minutes &gt;</type>
      <name>minutes</name>
      <anchorfile>namespaceenh.html</anchorfile>
      <anchor>aad379e78fcdc490e2fca2fe25344a4f6</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>timer&lt; period, std::chrono::hours &gt;</type>
      <name>hours</name>
      <anchorfile>namespaceenh.html</anchorfile>
      <anchor>af341f7f3c3c8279c4cc34a3451e86450</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr bool</type>
      <name>isGoodTimer_v</name>
      <anchorfile>namespaceenh.html</anchorfile>
      <anchor>a2d766edc467ea3fb7b3978e55129c445</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr bool</type>
      <name>isGoodTimerType_v</name>
      <anchorfile>namespaceenh.html</anchorfile>
      <anchor>a9620d58c64304582f23239af5662d60c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>logger.cpp</name>
    <path>F:/source/Enhance/src/</path>
    <filename>logger_8cpp.html</filename>
    <includes id="logger_8enh_8h" name="logger.enh.h" local="yes" imported="no">header/logger.enh.h</includes>
  </compound>
  <compound kind="class">
    <name>enh::blank_t</name>
    <filename>classenh_1_1blank__t.html</filename>
  </compound>
  <compound kind="class">
    <name>enh::counter</name>
    <filename>classenh_1_1counter.html</filename>
    <member kind="function">
      <type></type>
      <name>~counter</name>
      <anchorfile>classenh_1_1counter.html</anchorfile>
      <anchor>a904cbeef86a193a3104da1c7b59aee9c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>counter</name>
      <anchorfile>classenh_1_1counter.html</anchorfile>
      <anchor>ac17676ecd37a51462deda891b72071dc</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>counter</name>
      <anchorfile>classenh_1_1counter.html</anchorfile>
      <anchor>aa019f2621162fd44d77fd7159dc53044</anchor>
      <arglist>(const counter &amp;c) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>counter</name>
      <anchorfile>classenh_1_1counter.html</anchorfile>
      <anchor>a44435a62ea262bc06c0b052d04231489</anchor>
      <arglist>(counter &amp;&amp;c) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>counter</name>
      <anchorfile>classenh_1_1counter.html</anchorfile>
      <anchor>aeace6dbf5c23f86fc392aba13c129959</anchor>
      <arglist>(unsigned sec, unsigned min, unsigned hr, unsigned long long dy) noexcept</arglist>
    </member>
    <member kind="function">
      <type>counter &amp;</type>
      <name>operator=</name>
      <anchorfile>classenh_1_1counter.html</anchorfile>
      <anchor>a5f92ff48cc62c0ba8784fd9c36b698ca</anchor>
      <arglist>(const counter &amp;c) noexcept</arglist>
    </member>
    <member kind="function">
      <type>counter &amp;</type>
      <name>operator=</name>
      <anchorfile>classenh_1_1counter.html</anchorfile>
      <anchor>a7328668907dd222c2451794d52e46d25</anchor>
      <arglist>(counter &amp;&amp;c) noexcept</arglist>
    </member>
    <member kind="function">
      <type>counter &amp;</type>
      <name>reset</name>
      <anchorfile>classenh_1_1counter.html</anchorfile>
      <anchor>a70ef37aa21639eccf6aba14f305a8224</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>counter &amp;</type>
      <name>operator()</name>
      <anchorfile>classenh_1_1counter.html</anchorfile>
      <anchor>a968acd37a8b12b2ce16d806249ebfca6</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_seconds</name>
      <anchorfile>classenh_1_1counter.html</anchorfile>
      <anchor>af9ac0d8cc80bbafa5ea4bc365ae054b5</anchor>
      <arglist>(unsigned long long sec) noexcept</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>add_seconds</name>
      <anchorfile>classenh_1_1counter.html</anchorfile>
      <anchor>a737dde04340aa922f4368c569ae9ec94</anchor>
      <arglist>(unsigned long long sec) noexcept</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_minutes</name>
      <anchorfile>classenh_1_1counter.html</anchorfile>
      <anchor>acbed32dd24f87c815baf9ab6c26fdd46</anchor>
      <arglist>(unsigned long long min) noexcept</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>add_minutes</name>
      <anchorfile>classenh_1_1counter.html</anchorfile>
      <anchor>a5ea4ecb8ad6cdb1d3f7d8ac4fc6a6ecc</anchor>
      <arglist>(unsigned long long min) noexcept</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_hours</name>
      <anchorfile>classenh_1_1counter.html</anchorfile>
      <anchor>ace6b561e766168f0ef3723a727978504</anchor>
      <arglist>(unsigned long long hr) noexcept</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>add_hours</name>
      <anchorfile>classenh_1_1counter.html</anchorfile>
      <anchor>a78404712f9482d07bea47a7901549ca5</anchor>
      <arglist>(unsigned long long hr) noexcept</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_days</name>
      <anchorfile>classenh_1_1counter.html</anchorfile>
      <anchor>abc898d1d0b5d66d151a29e282bb2e068</anchor>
      <arglist>(unsigned long long dy) noexcept</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>add_days</name>
      <anchorfile>classenh_1_1counter.html</anchorfile>
      <anchor>a4eea8d14f83a40b427bc79deedd0c72d</anchor>
      <arglist>(unsigned long long dy) noexcept</arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>get_seconds</name>
      <anchorfile>classenh_1_1counter.html</anchorfile>
      <anchor>adde048f0acdf8f3c750d6272b1451fde</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>get_minutes</name>
      <anchorfile>classenh_1_1counter.html</anchorfile>
      <anchor>aa965ef27e8693cc6e1c48c0e01b6f80e</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>get_hours</name>
      <anchorfile>classenh_1_1counter.html</anchorfile>
      <anchor>a37df75488c0ec0b19b117ada6e82f31e</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>unsigned long long</type>
      <name>get_days</name>
      <anchorfile>classenh_1_1counter.html</anchorfile>
      <anchor>ae1cb08ba978b3c59207f18187de70e23</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>unsigned long long</type>
      <name>get_total_hours</name>
      <anchorfile>classenh_1_1counter.html</anchorfile>
      <anchor>aae1553f2a2c90bf7c9fd3cc595f288a9</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set</name>
      <anchorfile>classenh_1_1counter.html</anchorfile>
      <anchor>af29d417f920c6dbcfd908398bf296bb5</anchor>
      <arglist>(unsigned sec, unsigned min, unsigned hr, unsigned long long dy) noexcept</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>add</name>
      <anchorfile>classenh_1_1counter.html</anchorfile>
      <anchor>af620813e14986a8f9348d6feb7369043</anchor>
      <arglist>(unsigned sec, unsigned min, unsigned hr, unsigned long long dy)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>get_string</name>
      <anchorfile>classenh_1_1counter.html</anchorfile>
      <anchor>aeee74d1ecc2b2b13a3b6a56893b288ee</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>read_raw</name>
      <anchorfile>classenh_1_1counter.html</anchorfile>
      <anchor>a1e0617b1284046d52c31fff8b4cded6e</anchor>
      <arglist>(const char *raw, unsigned size)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>get_raw</name>
      <anchorfile>classenh_1_1counter.html</anchorfile>
      <anchor>a8a02b24c89216d73968defffeb8b9069</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&lt;</name>
      <anchorfile>classenh_1_1counter.html</anchorfile>
      <anchor>af88a31ba971f3ea3567755932ff4dc06</anchor>
      <arglist>(counter a) const noexcept</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&gt;</name>
      <anchorfile>classenh_1_1counter.html</anchorfile>
      <anchor>a54b4aa8e6462ebd5ba5984b0c1e95c3d</anchor>
      <arglist>(counter a) const noexcept</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator==</name>
      <anchorfile>classenh_1_1counter.html</anchorfile>
      <anchor>a77c834644c3b5cb240de0fee80353b2d</anchor>
      <arglist>(counter a) const noexcept</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&lt;=</name>
      <anchorfile>classenh_1_1counter.html</anchorfile>
      <anchor>ac6a1d3e25e9a61d996bf5c297f966150</anchor>
      <arglist>(counter a) const noexcept</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&gt;=</name>
      <anchorfile>classenh_1_1counter.html</anchorfile>
      <anchor>a3850e0ae998b9d3307ff7440d347394e</anchor>
      <arglist>(counter a) const noexcept</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static constexpr unsigned</type>
      <name>get_seconds_size</name>
      <anchorfile>classenh_1_1counter.html</anchorfile>
      <anchor>ab8015b93de2dac3968233339ecd8359e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static constexpr unsigned</type>
      <name>get_minutes_size</name>
      <anchorfile>classenh_1_1counter.html</anchorfile>
      <anchor>a74ec6323c545d6bfc0fc85c6934ce0b4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static constexpr unsigned</type>
      <name>get_hours_size</name>
      <anchorfile>classenh_1_1counter.html</anchorfile>
      <anchor>a41e05e8a86646e9c37dbd44971ea3fa0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static constexpr unsigned</type>
      <name>get_days_size</name>
      <anchorfile>classenh_1_1counter.html</anchorfile>
      <anchor>a006a2488fcf55a456b065ac525537e38</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static constexpr unsigned</type>
      <name>get_raw_size</name>
      <anchorfile>classenh_1_1counter.html</anchorfile>
      <anchor>a9cbb7cdc95816212461e0bd167d87965</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>enh::error_base</name>
    <filename>classenh_1_1error__base.html</filename>
    <templarg></templarg>
    <member kind="typedef">
      <type>type</type>
      <name>error</name>
      <anchorfile>classenh_1_1error__base.html</anchorfile>
      <anchor>a47deb7a12772f468c46e511debc6e077</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>error_base</name>
      <anchorfile>classenh_1_1error__base.html</anchorfile>
      <anchor>a9e5c40d11351522caafea384ca51c6e2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>clear</name>
      <anchorfile>classenh_1_1error__base.html</anchorfile>
      <anchor>a98fbeb022ce4c2357c5fd09f7b510d03</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>error</type>
      <name>getError</name>
      <anchorfile>classenh_1_1error__base.html</anchorfile>
      <anchor>ad441d16a1574e85baa29b00ff8540fac</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>checkFlag</name>
      <anchorfile>classenh_1_1error__base.html</anchorfile>
      <anchor>a42f2ac7fd83a7b9e2d5ad88211bbde3e</anchor>
      <arglist>(error check_flag) const noexcept</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isSafe</name>
      <anchorfile>classenh_1_1error__base.html</anchorfile>
      <anchor>a0abef11da38020a8358cfa381b9d876d</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Log</name>
      <anchorfile>classenh_1_1error__base.html</anchorfile>
      <anchor>a2921e99de5c1eb5f0b493159ffd04ab5</anchor>
      <arglist>(std::string file, std::string function, unsigned long line, std::string variable) const noexcept</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static constexpr error</type>
      <name>SAFE</name>
      <anchorfile>classenh_1_1error__base.html</anchorfile>
      <anchor>a53737218f4ba4028cb4c5261386581e8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static constexpr error</type>
      <name>UNKNOWN</name>
      <anchorfile>classenh_1_1error__base.html</anchorfile>
      <anchor>a96758f902259dabe544309442e6de195</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static constexpr error</type>
      <name>INVALID_ARG</name>
      <anchorfile>classenh_1_1error__base.html</anchorfile>
      <anchor>aa5fbeaaecc285fe80636fb36f2b81bed</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected">
      <type>tristate</type>
      <name>setFlag</name>
      <anchorfile>classenh_1_1error__base.html</anchorfile>
      <anchor>acae84344086ae45978078942867eeeae</anchor>
      <arglist>(error set) noexcept</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>tristate</type>
      <name>clearFlag</name>
      <anchorfile>classenh_1_1error__base.html</anchorfile>
      <anchor>ab8b7ad24b3354441f7b7c9493d6d5add</anchor>
      <arglist>(error bitClear) noexcept</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::atomic&lt; error &gt;</type>
      <name>flag</name>
      <anchorfile>classenh_1_1error__base.html</anchorfile>
      <anchor>a8f3b11b961414c6de399471481285cac</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>error_base&lt; unsigned char &gt;</name>
    <filename>classenh_1_1error__base.html</filename>
    <member kind="typedef">
      <type>unsigned char</type>
      <name>error</name>
      <anchorfile>classenh_1_1error__base.html</anchorfile>
      <anchor>a47deb7a12772f468c46e511debc6e077</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>error_base</name>
      <anchorfile>classenh_1_1error__base.html</anchorfile>
      <anchor>a9e5c40d11351522caafea384ca51c6e2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>clear</name>
      <anchorfile>classenh_1_1error__base.html</anchorfile>
      <anchor>a98fbeb022ce4c2357c5fd09f7b510d03</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>error</type>
      <name>getError</name>
      <anchorfile>classenh_1_1error__base.html</anchorfile>
      <anchor>ad441d16a1574e85baa29b00ff8540fac</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>checkFlag</name>
      <anchorfile>classenh_1_1error__base.html</anchorfile>
      <anchor>a42f2ac7fd83a7b9e2d5ad88211bbde3e</anchor>
      <arglist>(error check_flag) const noexcept</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isSafe</name>
      <anchorfile>classenh_1_1error__base.html</anchorfile>
      <anchor>a0abef11da38020a8358cfa381b9d876d</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Log</name>
      <anchorfile>classenh_1_1error__base.html</anchorfile>
      <anchor>a2921e99de5c1eb5f0b493159ffd04ab5</anchor>
      <arglist>(std::string file, std::string function, unsigned long line, std::string variable) const noexcept</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static constexpr error</type>
      <name>SAFE</name>
      <anchorfile>classenh_1_1error__base.html</anchorfile>
      <anchor>a53737218f4ba4028cb4c5261386581e8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static constexpr error</type>
      <name>UNKNOWN</name>
      <anchorfile>classenh_1_1error__base.html</anchorfile>
      <anchor>a96758f902259dabe544309442e6de195</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static constexpr error</type>
      <name>INVALID_ARG</name>
      <anchorfile>classenh_1_1error__base.html</anchorfile>
      <anchor>aa5fbeaaecc285fe80636fb36f2b81bed</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected">
      <type>tristate</type>
      <name>setFlag</name>
      <anchorfile>classenh_1_1error__base.html</anchorfile>
      <anchor>acae84344086ae45978078942867eeeae</anchor>
      <arglist>(error set) noexcept</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>tristate</type>
      <name>clearFlag</name>
      <anchorfile>classenh_1_1error__base.html</anchorfile>
      <anchor>ab8b7ad24b3354441f7b7c9493d6d5add</anchor>
      <arglist>(error bitClear) noexcept</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::atomic&lt; error &gt;</type>
      <name>flag</name>
      <anchorfile>classenh_1_1error__base.html</anchorfile>
      <anchor>a8f3b11b961414c6de399471481285cac</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>enh::gen_instruct</name>
    <filename>structenh_1_1gen__instruct.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <templarg></templarg>
  </compound>
  <compound kind="struct">
    <name>enh::quad_instruct</name>
    <filename>structenh_1_1quad__instruct.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <templarg></templarg>
    <templarg></templarg>
  </compound>
  <compound kind="class">
    <name>enh::queued_process</name>
    <filename>classenh_1_1queued__process.html</filename>
    <templarg></templarg>
    <base>error_base&lt; unsigned char &gt;</base>
    <member kind="typedef">
      <type>instruct</type>
      <name>info_type</name>
      <anchorfile>classenh_1_1queued__process.html</anchorfile>
      <anchor>a2cc8dbc12c9c5c730bc4b0c7ea71e2af</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::function&lt; tristate(info_type)&gt;</type>
      <name>processing_method</name>
      <anchorfile>classenh_1_1queued__process.html</anchorfile>
      <anchor>a12b0b1baf7ada84bc6ed4f7e21d3cd01</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>queued_process</name>
      <anchorfile>classenh_1_1queued__process.html</anchorfile>
      <anchor>ad317f28d15120a7098b1736609b1e469</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>queued_process</name>
      <anchorfile>classenh_1_1queued__process.html</anchorfile>
      <anchor>a92c180be267060ac350fb0d108c54e9f</anchor>
      <arglist>(processing_method msg) noexcept</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>RegisterProc</name>
      <anchorfile>classenh_1_1queued__process.html</anchorfile>
      <anchor>a63b2f078e4f940c1cc60876dd68e4cc5</anchor>
      <arglist>(processing_method in) noexcept</arglist>
    </member>
    <member kind="function">
      <type>tristate</type>
      <name>start_queue_process</name>
      <anchorfile>classenh_1_1queued__process.html</anchorfile>
      <anchor>a6f672330b15591f5efd9f24c02a7b130</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isQueueUpdated</name>
      <anchorfile>classenh_1_1queued__process.html</anchorfile>
      <anchor>a926883b08fdd0ece7ad199ec300d12cc</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>postMessage</name>
      <anchorfile>classenh_1_1queued__process.html</anchorfile>
      <anchor>a894cff5b159d6e41a6069dfc6d51e93d</anchor>
      <arglist>(info_type Message)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stopQueue</name>
      <anchorfile>classenh_1_1queued__process.html</anchorfile>
      <anchor>a8a2673b817a7fd554c9680e994a7d92c</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isQueueRunning</name>
      <anchorfile>classenh_1_1queued__process.html</anchorfile>
      <anchor>aa1c0dff80218f91894151034a422b3ee</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>WaitForQueueStop</name>
      <anchorfile>classenh_1_1queued__process.html</anchorfile>
      <anchor>a2d279f828b41dbd3bbdf931f8b86dc70</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>WaitForQueueEmpty</name>
      <anchorfile>classenh_1_1queued__process.html</anchorfile>
      <anchor>aa9e356200016900c12645f460095f1de</anchor>
      <arglist>(std::chrono::nanoseconds ns) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~queued_process</name>
      <anchorfile>classenh_1_1queued__process.html</anchorfile>
      <anchor>a322a0acb2e069b7961d34e58751a06ee</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static constexpr error</type>
      <name>NO_PROC</name>
      <anchorfile>classenh_1_1queued__process.html</anchorfile>
      <anchor>a16d88a2520417026bdbab73c858b01a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static constexpr error</type>
      <name>QUEUE_RUNNING</name>
      <anchorfile>classenh_1_1queued__process.html</anchorfile>
      <anchor>abd22ce8f0f7d0ce300995c24075264f2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>enh::timer</name>
    <filename>classenh_1_1timer.html</filename>
    <templarg>_per</templarg>
    <templarg></templarg>
    <member kind="typedef">
      <type>time_unit</type>
      <name>unit</name>
      <anchorfile>classenh_1_1timer.html</anchorfile>
      <anchor>a61193ea9c885539f6f161dbdbba040c7</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>timer</name>
      <anchorfile>classenh_1_1timer.html</anchorfile>
      <anchor>a239fa7d01dad0fb814fac5e32c6ecdce</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~timer</name>
      <anchorfile>classenh_1_1timer.html</anchorfile>
      <anchor>a3bbc6655717f6a1799ae594c6117fe68</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>unsigned long long</type>
      <name>wait</name>
      <anchorfile>classenh_1_1timer.html</anchorfile>
      <anchor>a1ac9c2141748d87218f6e6e25d1f12a7</anchor>
      <arglist>(unsigned long long expected) noexcept</arglist>
    </member>
    <member kind="function">
      <type>unsigned long long</type>
      <name>wait</name>
      <anchorfile>classenh_1_1timer.html</anchorfile>
      <anchor>ae43edb6c5742ff88b1dbc04d7433adf2</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>long long</type>
      <name>wait_for</name>
      <anchorfile>classenh_1_1timer.html</anchorfile>
      <anchor>a1ea21820b2cbd14f7829dbd6ca2fb6e7</anchor>
      <arglist>(unsigned mult_count, std::function&lt; bool()&gt; condition) noexcept</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stop</name>
      <anchorfile>classenh_1_1timer.html</anchorfile>
      <anchor>aa4f008a170349f9dfbcbbab06b1a6568</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>clear_stop</name>
      <anchorfile>classenh_1_1timer.html</anchorfile>
      <anchor>a985cc617da6ef87ee8e41b1f04937206</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>unsigned long long</type>
      <name>elapsed</name>
      <anchorfile>classenh_1_1timer.html</anchorfile>
      <anchor>a919d51a7d1c80ac7f3b2fce93fe372d4</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>unsigned long long</type>
      <name>wait_for</name>
      <anchorfile>classenh_1_1timer.html</anchorfile>
      <anchor>a88634683b66dea62a93b94125c94dc16</anchor>
      <arglist>(unsigned long mult_count) noexcept</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isTimerCounting</name>
      <anchorfile>classenh_1_1timer.html</anchorfile>
      <anchor>afbc68a8aa10a536e7102543e2695cff8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>start_timer</name>
      <anchorfile>classenh_1_1timer.html</anchorfile>
      <anchor>a61e70ea33b8c1953895911a4c975e0a1</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator!</name>
      <anchorfile>classenh_1_1timer.html</anchorfile>
      <anchor>a6197461f72ef9cbafa724a75bb4c4cb1</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>join</name>
      <anchorfile>classenh_1_1timer.html</anchorfile>
      <anchor>a1ed629b20f8a5f3953aaa419b9190690</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>force_join</name>
      <anchorfile>classenh_1_1timer.html</anchorfile>
      <anchor>a2b6b981072b85d7a70c46f4767d3fc90</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static time_pt</type>
      <name>program_start_point</name>
      <anchorfile>classenh_1_1timer.html</anchorfile>
      <anchor>a190209fcccca57083a53b7e36781939f</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static unit</type>
      <name>program_elapsed</name>
      <anchorfile>classenh_1_1timer.html</anchorfile>
      <anchor>ad649090fc3529e98fba7291057413197</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static constexpr unsigned</type>
      <name>period</name>
      <anchorfile>classenh_1_1timer.html</anchorfile>
      <anchor>a2f0a2898835b8e59d07923ddd4526697</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>enh::version_info</name>
    <filename>classenh_1_1version__info.html</filename>
    <member kind="function">
      <type></type>
      <name>version_info</name>
      <anchorfile>classenh_1_1version__info.html</anchorfile>
      <anchor>a16c073bdc25b91acfb5e7d8f1b751aaf</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr</type>
      <name>version_info</name>
      <anchorfile>classenh_1_1version__info.html</anchorfile>
      <anchor>a89adefd30b10328224b16dcc4fecba73</anchor>
      <arglist>(unsigned mj, unsigned mn, unsigned rv, unsigned long bld, rel_type tp) noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr</type>
      <name>version_info</name>
      <anchorfile>classenh_1_1version__info.html</anchorfile>
      <anchor>a6e34f4b25b00be1d37908f1d2c63d58d</anchor>
      <arglist>(unsigned mj, unsigned mn, unsigned rv, unsigned long bld, rel_type tp, std::string_view rep) noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr unsigned</type>
      <name>get_major</name>
      <anchorfile>classenh_1_1version__info.html</anchorfile>
      <anchor>a1f4bc3420fa36c34970ae7a4c89b8852</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr unsigned</type>
      <name>get_minor</name>
      <anchorfile>classenh_1_1version__info.html</anchorfile>
      <anchor>a4563654e649482634b3becc067e06ac5</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr unsigned</type>
      <name>get_revision</name>
      <anchorfile>classenh_1_1version__info.html</anchorfile>
      <anchor>abcdc1a0d44d2a14ae3eaff3671e4934d</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr unsigned long</type>
      <name>get_build</name>
      <anchorfile>classenh_1_1version__info.html</anchorfile>
      <anchor>a33817d135f7181ee91adc66d043dc53e</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr rel_type</type>
      <name>get_type</name>
      <anchorfile>classenh_1_1version__info.html</anchorfile>
      <anchor>a89e9d440e0d7e332235cec2548e6545e</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr std::string_view</type>
      <name>string</name>
      <anchorfile>classenh_1_1version__info.html</anchorfile>
      <anchor>a055ffb8eb57bc6a72bf7195ef9046f15</anchor>
      <arglist>() const noexcept</arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>debug</name>
    <filename>namespacedebug.html</filename>
    <member kind="function">
      <type>std::filesystem::path</type>
      <name>getFile</name>
      <anchorfile>namespacedebug.html</anchorfile>
      <anchor>a89c8e27f837f3ee4e4fce0b46ae82ccf</anchor>
      <arglist>(std::thread::id id, std::string function)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Log</name>
      <anchorfile>namespacedebug.html</anchorfile>
      <anchor>a24f177f77e5c8af3922ada72aea089ac</anchor>
      <arglist>(std::string lg, std::string function)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Log</name>
      <anchorfile>namespacedebug.html</anchorfile>
      <anchor>a734ce3feb2187ac6495262f52f7b3753</anchor>
      <arglist>(std::string file, std::string function, unsigned long line)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Log</name>
      <anchorfile>namespacedebug.html</anchorfile>
      <anchor>ae5935b08444a6013a0f16fd8a0e2900d</anchor>
      <arglist>(std::string file, std::string function, unsigned long line, std::string descr)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Log</name>
      <anchorfile>namespacedebug.html</anchorfile>
      <anchor>a717f2ef93984eb5de567d96bc78ede21</anchor>
      <arglist>(std::string file, std::string function, unsigned long line, std::string var, const T &amp;val)</arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>enh</name>
    <filename>namespaceenh.html</filename>
    <class kind="class">enh::blank_t</class>
    <class kind="class">enh::counter</class>
    <class kind="class">enh::error_base</class>
    <class kind="struct">enh::gen_instruct</class>
    <class kind="struct">enh::quad_instruct</class>
    <class kind="class">enh::queued_process</class>
    <class kind="class">enh::timer</class>
    <class kind="class">enh::version_info</class>
    <member kind="typedef">
      <type>std::chrono::high_resolution_clock</type>
      <name>high_res</name>
      <anchorfile>namespaceenh.html</anchorfile>
      <anchor>aa3b22608dd9a6d477676c2d5580f09b9</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>decltype(high_res::now())</type>
      <name>time_pt</name>
      <anchorfile>namespaceenh.html</anchorfile>
      <anchor>a8f5724afac4fbbae9067dbc98fa4e7d8</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>timer&lt; 50, std::chrono::nanoseconds &gt;</type>
      <name>nanos</name>
      <anchorfile>namespaceenh.html</anchorfile>
      <anchor>a40787cb24d744d28ea8b7105af612f81</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>timer&lt; 50, std::chrono::microseconds &gt;</type>
      <name>micros</name>
      <anchorfile>namespaceenh.html</anchorfile>
      <anchor>a4161dbe2decf77ed6da3d93d5ed14c9d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>timer&lt; period, std::chrono::milliseconds &gt;</type>
      <name>millis</name>
      <anchorfile>namespaceenh.html</anchorfile>
      <anchor>abaa97670f060ac3bf5704a6c3350e8bb</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>timer&lt; period, std::chrono::seconds &gt;</type>
      <name>seconds</name>
      <anchorfile>namespaceenh.html</anchorfile>
      <anchor>a0e90f21da57b74c795abcad09d29622a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>timer&lt; period, std::chrono::minutes &gt;</type>
      <name>minutes</name>
      <anchorfile>namespaceenh.html</anchorfile>
      <anchor>aad379e78fcdc490e2fca2fe25344a4f6</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>timer&lt; period, std::chrono::hours &gt;</type>
      <name>hours</name>
      <anchorfile>namespaceenh.html</anchorfile>
      <anchor>af341f7f3c3c8279c4cc34a3451e86450</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>tristate</name>
      <anchorfile>namespaceenh.html</anchorfile>
      <anchor>a61067ccf704a6ec6d8a407f8394b004b</anchor>
      <arglist></arglist>
      <enumvalue file="namespaceenh.html" anchor="a61067ccf704a6ec6d8a407f8394b004ba45802158e78dd9584161629098018fe8">GOOD</enumvalue>
      <enumvalue file="namespaceenh.html" anchor="a61067ccf704a6ec6d8a407f8394b004babb1ca97ec761fc37101737ba0aa2e7c5">ERROR</enumvalue>
      <enumvalue file="namespaceenh.html" anchor="a61067ccf704a6ec6d8a407f8394b004ba0205fe53d2d6958c15ab0aaee27b060f">PREV_ERR</enumvalue>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>rel_type</name>
      <anchorfile>namespaceenh.html</anchorfile>
      <anchor>a0b0e871be4713899208ceba5d9b14172</anchor>
      <arglist></arglist>
      <enumvalue file="namespaceenh.html" anchor="a0b0e871be4713899208ceba5d9b14172a36b84f8e3fba5bf993e3ba352d62d146">BETA</enumvalue>
      <enumvalue file="namespaceenh.html" anchor="a0b0e871be4713899208ceba5d9b14172a7d649ef069df9885e382417c79f3d5cd">RELEASE</enumvalue>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator!</name>
      <anchorfile>namespaceenh.html</anchorfile>
      <anchor>a812420b64dc76bb983d6b627c9e433a2</anchor>
      <arglist>(tristate e) noexcept</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>checkField</name>
      <anchorfile>namespaceenh.html</anchorfile>
      <anchor>a5084827e591e0425d76b9752ae751794</anchor>
      <arglist>(enumT in, enumT field) noexcept</arglist>
    </member>
    <member kind="function">
      <type>counter</type>
      <name>max</name>
      <anchorfile>namespaceenh.html</anchorfile>
      <anchor>a5f461456cf52f5d925004b085dd84761</anchor>
      <arglist>(const counter a, const counter b) noexcept</arglist>
    </member>
    <member kind="function">
      <type>counter</type>
      <name>min</name>
      <anchorfile>namespaceenh.html</anchorfile>
      <anchor>af17a502dc7630b917abc0c438cbfb18c</anchor>
      <arglist>(const counter a, const counter b) noexcept</arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>namespaceenh.html</anchorfile>
      <anchor>a51d3bfd96daf7772870f6390df3a1d00</anchor>
      <arglist>(std::ostream &amp;out, counter ct) noexcept</arglist>
    </member>
    <member kind="variable">
      <type>constexpr short</type>
      <name>signum</name>
      <anchorfile>namespaceenh.html</anchorfile>
      <anchor>a1373aa9e1df59df05a38e668bd25402b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr unsigned long long</type>
      <name>inclusive_ratio</name>
      <anchorfile>namespaceenh.html</anchorfile>
      <anchor>a3749434e1f10c025f00032a51f2aba25</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr version_info</type>
      <name>enhance_version</name>
      <anchorfile>namespaceenh.html</anchorfile>
      <anchor>a0dbd8c46a7fbad18f9f73298a9b9b88a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr bool</type>
      <name>isGoodTimer_v</name>
      <anchorfile>namespaceenh.html</anchorfile>
      <anchor>a2d766edc467ea3fb7b3978e55129c445</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr bool</type>
      <name>isGoodTimerType_v</name>
      <anchorfile>namespaceenh.html</anchorfile>
      <anchor>a9620d58c64304582f23239af5662d60c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="page">
    <name>md_F:_source_Enhance_License</name>
    <title>License</title>
    <filename>md__f_1_source__enhance__license</filename>
  </compound>
  <compound kind="page">
    <name>index</name>
    <title>ENHANCE</title>
    <filename>index</filename>
  </compound>
</tagfile>
