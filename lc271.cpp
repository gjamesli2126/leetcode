#include <bits/stdc++.h>
using namespace std;
#define mainTest main

class Codec {
public:
    // Encodes a list of strings to a single string.
    string encode(vector<string>& strs) {
        string str;
        for(const string& s:strs){//pattern: 5$words6$...
            str+=to_string(s.length());
            str+='$';
            str+=s;

        }
        return str;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(string s) {
        int len=int(s.length());
        string eachS;
        vector<string> ans;
        for(int i=0;i<len;++i){
            char c=s[i];
            if(c!='$'){
                eachS+=c;
                continue;
            }
            int eachLen=stoi(eachS);
            eachS.clear();
            for(int j=1;j<=eachLen;++j) eachS+=s[i+j];
            ans.push_back(eachS);
            eachS.clear();
            i+=eachLen;
        }
        return ans;
    }
};

int mainTest() {
    // Create an instance of the Codec class
    Codec codec;

    // Define a series of test cases
    vector<vector<string>> testCases = {
            {"Hello", "World"}, // Example 1
            {""},               // Example 2
            {"Hello", "", "World", "!"}, // Additional test case
            {"63/Rc","h","BmI3FS~J9#vmk","7uBZ?7*/","24h+X","O "},
            {"3OiuTG]77azCi=unYZPD;J,]!jc{-2io2QbzF@]Mteh0%{uZ^xjdX%z~z7&q`@E!\",\" R52b]L.Ocq9^2t*uP!S<39As.O=bNc:ZNxl(z9kt>j*6cpwtxls#gueVi VD\",\"HpXlc.B*+V^eCpJf5&Q_f.Fvt,T+g,`Q&ZRrkp!nN/wxwV-+Lvonxg_i] 1^4A^+dW,%xR++>QJZiwVBtjTGj[EGmZTF\",\"~-#~+/ug(NS%WL )M+#YL{/tB)6|/!|gr5)>l7(M,5&C(MQGbm<]pYJ@88`9nt7\",\"[sQ#}Q*vV$5uoP`]OCyd5*}X/nRqp\",\"HODA`e|ot@cb_\",\"skuf0SLyF[kdT>Y,2sT5WMnZWHsta8.<DAE,,HeR7pk3N-2lFj)Z~{}4Vaj{Vc>l#w#\",\"rd`n$6t#jLkxm,ZjFOtY[wQx?#2SW;lwm52Q4cgw|We768OMkz`?izlP1++#=SgV6+}K}F=R4{oC/X0n2z^0A3#2 !@rpA)ybo\",\"@N3#/aZ~Cp]^L[?l@q5gzEv-QrOR+%7R/hG%-L;=UM)H0:;FJ(-*ve0I;i!h%y9Q 6!sG*y)NP[|N:..+th~(WGGvKYJ@w)\",\"0pok\",\"nXP&ra&af!Ps5TeQB}h362-(5V1F9JPgu}}W!mbB]Desm(\",\"881Ja+c~h2$ISOrEBA73VGLo}T7D+)yrk4{+,Wf@6dPstnat6>%uw4MPiPWPuI&{e7LF.5Z5O6;TJ1rFHg_IG4X+!J?\",\"2lMDTy&U%{k6dq{R]BRh7I=9[S4`YQOqz%wi\",\"RpH/^)@<B<7m:i(;OJ1R;WK55\",\".crhQGPnby6W@C3N9IQy\",\"4#nT(ym#;tko [V>p(sU>Ko-J0s%wP+/UIAF&rq<_KvN[F~*#kyMJB;u>%bBB@rbJ{Bv2L2Ctil1v|X]Oyul}jDXMH11one*/kQ\",\"eFw)1a^HcWH^*VA1v9` Q26q|lDY4h2K|{}#b>w&>:Vp;7F*VS&w927(9+L$OB^[u3v;2BV\",\"4E6Z.;QE&z&S.E)mg#A+I6qb9l3G(k0a@bDl&|u3hZ{P$6SJ Tj{X_el,?%)4zAlQwb50#@\",\":Ravo4.~Pr0)ly7-id3|e!/+y?nVp9i[GmnP5ESe6o`6ASVV(g8SkSyUwM5HKU#-ww{D)_K.=*Ti,\",\"%ui|p>= .[\",\"ignmo94Tt45OBxF/-~~_A.BT0.E]ucZ~biqsN/G<O,M->]~lD<\",\"lkAB.TP=\",\"k<K>=^!cTJ&|os1VS52Hu.&1{tY/2v;suufF9$Sgo U qW7^ ,MR?+|JY&}2[s;Y*CE<3;dY.ka}Wjc4%C+yXm}@fEy9,cvhB\",\"RJqTKZ>Y/6cd4j.l>aZ#T"}
            // Add more test cases as needed
    };

    // Iterate through each test case
    for (int i = 0; i < testCases.size(); ++i) {
        // Encode the list of strings
        string encoded = codec.encode(testCases[i]);

        // Decode the string back to the list of strings
        vector<string> decoded = codec.decode(encoded);

        // Determine if the test case passed or failed
        bool status = (decoded == testCases[i]);

        // Print the test results
        cout << "Test " << i + 1 << ": ";
        cout << "Input: [";
        for (size_t j = 0; j < testCases[i].size(); ++j) {
            cout << "\"" << testCases[i][j] << "\"" << (j < testCases[i].size() - 1 ? ", " : "");
        }
        cout << "]; ";
        cout << "Encoded: \"" << encoded << "\"; ";
        cout << "Decoded: [";
        for (size_t j = 0; j < decoded.size(); ++j) {
            cout << "\"" << decoded[j] << "\"" << (j < decoded.size() - 1 ? ", " : "");
        }
        cout << "]; ";
        cout << "Status: " << (status ? "PASS" : "FAIL") << endl;
    }

    return 0;
}
