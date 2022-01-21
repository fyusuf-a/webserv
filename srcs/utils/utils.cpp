#include "utils.hpp"
#include <algorithm>
#include <cctype>
#include <iomanip>
#include <fcntl.h>


namespace Utils
{
	bool cmpCharInsensitive::operator() (const unsigned char a, const unsigned char b) {
		return ::tolower(a) < tolower(b);
	}

	bool cmpStringInsensitive::operator()(const std::string& a, const std::string& b) const {
		return is_less(a, b);
	}

	bool cmpStringInsensitive::is_less(const std::string& a, const std::string& b) {
		return std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end(), cmpCharInsensitive());
	}

	bool cmpStringInsensitive::is_equal(const std::string& a, const std::string& b) {
		return !is_less(a,b) && !is_less(b, a);
	}

	std::string month_to_str(unsigned int i) {
		static std::map<char, std::string> month_to_str;
		if (month_to_str.empty()) {
			month_to_str[0] = "Jan";
			month_to_str[1] = "Feb";
			month_to_str[2] = "Mar";
			month_to_str[3] = "Apr";
			month_to_str[4] = "May";
			month_to_str[5] = "Jun";
			month_to_str[6] = "Jul";
			month_to_str[7] = "Aug";
			month_to_str[8] = "Sep";
			month_to_str[9] = "Oct";
			month_to_str[10] = "Nov";
			month_to_str[11] = "Dec";
		}
		if (i > 11)
			return "";
		return month_to_str[i];
	}

	std::string weekday_to_str(unsigned int i) {
		static std::map<char, std::string> weekday_to_str;
		if (weekday_to_str.empty()) {
			weekday_to_str[0] = "Sun";
			weekday_to_str[1] = "Mon";
			weekday_to_str[2] = "Tue";
			weekday_to_str[3] = "Wed";
			weekday_to_str[4] = "Thu";
			weekday_to_str[5] = "Fri";
			weekday_to_str[6] = "Sat";
		}
		if (i > 11)
			return "";
		return weekday_to_str[i];
	}

	std::ostream & print_date(std::ostream& os, bool show_weekday, bool show_gmt) {
		time_t rawtime;
		time(&rawtime);
		struct tm* t = localtime(&rawtime);
		if (show_weekday)
			os << weekday_to_str(t->tm_wday) << ", ";
		os << std::setfill('0') << std::setw(2) << t->tm_mday << " "
			<< std::setfill('0') << std::setw(2) << month_to_str(t->tm_mon)
			<< " " << std::setw(4) << (1900 + t->tm_year) << " " 
			<< std::setfill('0') << std::setw(2) << t->tm_hour << ":"
			<< std::setfill('0') << std::setw(2) << t->tm_min << ":"
			<< std::setfill('0') << std::setw(2) << t->tm_sec;
		if (show_gmt)
			os << " GMT";
		return os;
	}

    bool is_space(char c)
    {
        if ((c >= 9 && c <= 13) || c == 32 || c == '\t')
            return (true);
        return (false);
    }
    bool is_spaces(std::string const s)
    {
        for (int i =  0; s[i]; i++)
            if (!is_space(s[i]))
                return (false);
        return (true);
    }
    bool is_valid_directive(std::string const &dir)
    {
        if (dir == "index" || dir == "root" || dir == "server_name"
        || dir == "listen" || dir == "host" || dir == "error"
        || dir == "cgi_extension" || dir == "cgi_bin")
            return (true);
        return (false);
    }
    bool is_valid_directive_location(std::string const &dir)
    {
        if (dir == "index" || dir == "methods" || dir == "cgi_extension"
        || dir == "cgi_bin" || dir == "language" || dir == "autoindex" || dir == "root"
        || dir == "client_max_body_size" || dir == "auth_basic" || dir == "auth_basic_user_file" || dir == "redirection")
            return (true);
        return (false);
    }
    bool is_valid_methods(std::string const &dir)
    {
        if (dir == "GET" || dir == "POST" || dir == "DELETE")
            return (true);
        return (false);
    }
    bool is_valid(std::string& str, std::string const& val)
    {
        size_t found;

        found = str.find(val);
        if (found != std::string::npos)
        {
            for (size_t i = val.size(); i != str.size(); i++)
                if (!Utils::is_space(str[i]))
                    return (false);
            str = val;
            return (true);
        }
        return (false);
    }
    bool is_digit(char const c)
    {
        if (c >= '0' && c <= '9')
            return (true);
        return (false); 
    }
    bool is_digits(std::string const &str)
    {
        for (int i =  0; str[i]; i++)
            if (!is_digit(str[i]) && str[i] != '-')
                return (false);
        return (true);
    }
    void ft_trim(std::string &str)
    {
        while(!str.empty() && std::isspace(*str.begin()))
            str.erase(str.begin());
        
        while (!str.empty() && Utils::is_space(*str.rbegin()))
            str.erase(str.size() - 1);
    }
    bool is_comentary(std::string &str)
    {
        size_t i = str.find("#", 0);

        if (i == 0)
        {
            return (true);
        }
        if (i != std::string::npos)
        {
            str.erase(i, str.size());

            return (false);
        }
        else
            return (false);
        return (true);
    }
    int ft_find(std::string str, std::string find)
    {
        size_t i = 0;
        for (; str[i] == find[i]; i++);

        if (i < str.size())
            return (0);
        return (i);
    }

    bool         is_file(const char *path) 
    {
        struct stat s;

        if (!stat(path, &s) && !(s.st_mode & S_IFDIR))
                return (true);
         return (false);
    }
    int is_dir(const char *name)
    {
        int ret = 0;
        DIR* rep = opendir(name);
        
        if(rep != NULL)
        {
            closedir(rep);
            ret = 1;
        }
    
        return ret;
    }

    std::string toString(int &i)
    {
        std::stringstream ss;
        ss << i;
        return ss.str();
    }

	bool set_fd_as_non_blocking(int fd, const char* fd_description) {
		if (fcntl(fd, F_SETFL, O_NONBLOCK) < 0)
		{
			Log::getInstance().error() << "cannot set " << fd_description << " as nonblocking" << std::endl;
			return false;
		}
		return true;
	}

    bool        next_chars_code(std::string str, std::size_t i) {
        static const std::string base1 = "0123456789ABCDEF";
        static const std::string base2 = "0123456789abcdef";

        if (!str[i] || (base1.find(str[i]) == std::string::npos && base2.find(str[i]) == std::string::npos))
            return (false);
        ++i;
        if (!str[i] || (base1.find(str[i]) == std::string::npos && base2.find(str[i]) == std::string::npos))
            return (false);
        return (true);
    }

    std::size_t find_value(char val) {
        static const std::string base1 = "0123456789ABCDEF";
        static const std::string base2 = "0123456789abcdef";

        if (base1.find(val) != std::string::npos)
            return (base1.find(val));
        else
            return (base2.find(val));

    }

    std::string percent_decode(const std::string str) {
        std::string decoded;
        std::size_t i = 0;
        char ascii;

        while (str[i]) {
            if (str[i] == '%' && next_chars_code(str, i + 1)) {
                ascii = 0;
                i++;
                ascii += find_value(str[i]) * 16;
                i++;
                ascii += find_value(str[i]);
                decoded += ascii;
            }
            else 
                decoded += str[i];
            i++;
        }
        return (decoded);
    }
    
    std::string percent_encode(const std::string str) {
        std::string encoded;
        std::size_t i = 0;
        int first_dig = 0;
        static std::string base = "0123456789ABCDEF";
        char c;

        while (str[i]) {
            c = str[i];
            if (c != '!' && (c < '#' || c > ',') && c != '/' && c != ':' && c != ';' && c != '=' && c != '?' && c != '@' && c != '[' && c != ']')
                encoded += str[i];
            else {
                encoded += '%';
                first_dig = str[i] / 16;
                encoded += base[first_dig];
                encoded += base[str[i] - first_dig * 16];
            }
            i++;
        }
        return (encoded);
    }

	std::string find_mime_type(std::string& ext) {
		static std::map<std::string, std::string> mime_types;
		if (mime_types.empty()) {
			mime_types["123"] = "application/vnd.lotus-1-2-3";
			mime_types["1km"] = "application/vnd.1000minds.decision-model+xml";
			mime_types["3dml"] = "text/vnd.in3d.3dml";
			mime_types["3ds"] = "image/x-3ds";
			mime_types["3g2"] = "video/3gpp2";
			mime_types["3gp"] = "video/3gpp";
			mime_types["3gpp"] = "video/3gpp";
			mime_types["3mf"] = "model/3mf";
			mime_types["7z"] = "application/x-7z-compressed";
			mime_types["aab"] = "application/x-authorware-bin";
			mime_types["u32"] = "application/x-authorware-bin";
			mime_types["vox"] = "application/x-authorware-bin";
			mime_types["x32"] = "application/x-authorware-bin";
			mime_types["aac"] = "audio/x-aac";
			mime_types["aam"] = "application/x-authorware-map";
			mime_types["aas"] = "application/x-authorware-seg";
			mime_types["abw"] = "application/x-abiword";
			mime_types["ac"] = "application/vnd.nokia.n-gage.ac+xml";
			mime_types["acc"] = "application/vnd.americandynamics.acc";
			mime_types["ace"] = "application/x-ace-compressed";
			mime_types["acu"] = "application/vnd.acucobol";
			mime_types["acutc"] = "application/vnd.acucorp";
			mime_types["atc"] = "application/vnd.acucorp";
			mime_types["adp"] = "audio/adpcm";
			mime_types["aep"] = "application/vnd.audiograph";
			mime_types["afm"] = "application/x-font-type1";
			mime_types["pfa"] = "application/x-font-type1";
			mime_types["pfb"] = "application/x-font-type1";
			mime_types["pfm"] = "application/x-font-type1";
			mime_types["afp"] = "application/vnd.ibm.modcap";
			mime_types["list3820"] = "application/vnd.ibm.modcap";
			mime_types["listafp"] = "application/vnd.ibm.modcap";
			mime_types["ahead"] = "application/vnd.ahead.space";
			mime_types["ai"] = "application/postscript";
			mime_types["eps"] = "application/postscript";
			mime_types["ps"] = "application/postscript";
			mime_types["aif"] = "audio/x-aiff";
			mime_types["aifc"] = "audio/x-aiff";
			mime_types["aiff"] = "audio/x-aiff";
			mime_types["air"] = "application/vnd.adobe.air-application-installer-package+zip";
			mime_types["ait"] = "application/vnd.dvb.ait";
			mime_types["ami"] = "application/vnd.amiga.ami";
			mime_types["apk"] = "application/vnd.android.package-archive";
			mime_types["apng"] = "image/apng";
			mime_types["appcache"] = "text/cache-manifest";
			mime_types["manifest"] = "text/cache-manifest";
			mime_types["application"] = "application/x-ms-application";
			mime_types["apr"] = "application/vnd.lotus-approach";
			mime_types["arc"] = "application/x-freearc";
			mime_types["arj"] = "application/x-arj";
			mime_types["asc"] = "application/pgp-signature";
			mime_types["sig"] = "application/pgp-signature";
			mime_types["asf"] = "video/x-ms-asf";
			mime_types["asx"] = "video/x-ms-asf";
			mime_types["asm"] = "text/x-asm";
			mime_types["s"] = "text/x-asm";
			mime_types["aso"] = "application/vnd.accpac.simply.aso";
			mime_types["atom"] = "application/atom+xml";
			mime_types["atomcat"] = "application/atomcat+xml";
			mime_types["atomdeleted"] = "application/atomdeleted+xml";
			mime_types["atomsvc"] = "application/atomsvc+xml";
			mime_types["atx"] = "application/vnd.antix.game-component";
			mime_types["au"] = "audio/basic";
			mime_types["snd"] = "audio/basic";
			mime_types["avi"] = "video/x-msvideo";
			mime_types["avif"] = "image/avif";
			mime_types["aw"] = "application/applixware";
			mime_types["azf"] = "application/vnd.airzip.filesecure.azf";
			mime_types["azs"] = "application/vnd.airzip.filesecure.azs";
			mime_types["azv"] = "image/vnd.airzip.accelerator.azv";
			mime_types["azw"] = "application/vnd.amazon.ebook";
			mime_types["b16"] = "image/vnd.pco.b16";
			mime_types["bat"] = "application/x-msdownload";
			mime_types["com"] = "application/x-msdownload";
			mime_types["dll"] = "application/x-msdownload";
			mime_types["exe"] = "application/x-msdownload";
			mime_types["msi"] = "application/x-msdownload";
			mime_types["bcpio"] = "application/x-bcpio";
			mime_types["bdf"] = "application/x-font-bdf";
			mime_types["bdm"] = "application/vnd.syncml.dm+wbxml";
			mime_types["bdoc"] = "application/x-bdoc";
			mime_types["bed"] = "application/vnd.realvnc.bed";
			mime_types["bh2"] = "application/vnd.fujitsu.oasysprs";
			mime_types["bin"] = "application/octet-stream";
			mime_types["bpk"] = "application/octet-stream";
			mime_types["buffer"] = "application/octet-stream";
			mime_types["deploy"] = "application/octet-stream";
			mime_types["dist"] = "application/octet-stream";
			mime_types["distz"] = "application/octet-stream";
			mime_types["dms"] = "application/octet-stream";
			mime_types["dump"] = "application/octet-stream";
			mime_types["elc"] = "application/octet-stream";
			mime_types["img"] = "application/octet-stream";
			mime_types["lrf"] = "application/octet-stream";
			mime_types["mar"] = "application/octet-stream";
			mime_types["msm"] = "application/octet-stream";
			mime_types["msp"] = "application/octet-stream";
			mime_types["pkg"] = "application/octet-stream";
			mime_types["so"] = "application/octet-stream";
			mime_types["blb"] = "application/x-blorb";
			mime_types["blorb"] = "application/x-blorb";
			mime_types["bmi"] = "application/vnd.bmi";
			mime_types["bmml"] = "application/vnd.balsamiq.bmml+xml";
			mime_types["bmp"] = "image/x-ms-bmp";
			mime_types["book"] = "application/vnd.framemaker";
			mime_types["fm"] = "application/vnd.framemaker";
			mime_types["frame"] = "application/vnd.framemaker";
			mime_types["maker"] = "application/vnd.framemaker";
			mime_types["box"] = "application/vnd.previewsystems.box";
			mime_types["boz"] = "application/x-bzip2";
			mime_types["bz2"] = "application/x-bzip2";
			mime_types["bsp"] = "model/vnd.valve.source.compiled-map";
			mime_types["btif"] = "image/prs.btif";
			mime_types["bz"] = "application/x-bzip";
			mime_types["c"] = "text/x-c";
			mime_types["cc"] = "text/x-c";
			mime_types["cpp"] = "text/x-c";
			mime_types["cxx"] = "text/x-c";
			mime_types["dic"] = "text/x-c";
			mime_types["h"] = "text/x-c";
			mime_types["hh"] = "text/x-c";
			mime_types["c11amc"] = "application/vnd.cluetrust.cartomobile-config";
			mime_types["c11amz"] = "application/vnd.cluetrust.cartomobile-config-pkg";
			mime_types["c4d"] = "application/vnd.clonk.c4group";
			mime_types["c4f"] = "application/vnd.clonk.c4group";
			mime_types["c4g"] = "application/vnd.clonk.c4group";
			mime_types["c4p"] = "application/vnd.clonk.c4group";
			mime_types["c4u"] = "application/vnd.clonk.c4group";
			mime_types["cab"] = "application/vnd.ms-cab-compressed";
			mime_types["caf"] = "audio/x-caf";
			mime_types["cap"] = "application/vnd.tcpdump.pcap";
			mime_types["dmp"] = "application/vnd.tcpdump.pcap";
			mime_types["pcap"] = "application/vnd.tcpdump.pcap";
			mime_types["car"] = "application/vnd.curl.car";
			mime_types["cat"] = "application/vnd.ms-pki.seccat";
			mime_types["cb7"] = "application/x-cbr";
			mime_types["cba"] = "application/x-cbr";
			mime_types["cbr"] = "application/x-cbr";
			mime_types["cbt"] = "application/x-cbr";
			mime_types["cbz"] = "application/x-cbr";
			mime_types["cco"] = "application/x-cocoa";
			mime_types["cct"] = "application/x-director";
			mime_types["cst"] = "application/x-director";
			mime_types["cxt"] = "application/x-director";
			mime_types["dcr"] = "application/x-director";
			mime_types["dir"] = "application/x-director";
			mime_types["dxr"] = "application/x-director";
			mime_types["fgd"] = "application/x-director";
			mime_types["swa"] = "application/x-director";
			mime_types["w3d"] = "application/x-director";
			mime_types["ccxml"] = "application/ccxml+xml";
			mime_types["cdbcmsg"] = "application/vnd.contact.cmsg";
			mime_types["cdf"] = "application/x-netcdf";
			mime_types["nc"] = "application/x-netcdf";
			mime_types["cdfx"] = "application/cdfx+xml";
			mime_types["cdkey"] = "application/vnd.mediastation.cdkey";
			mime_types["cdmia"] = "application/cdmi-capability";
			mime_types["cdmic"] = "application/cdmi-container";
			mime_types["cdmid"] = "application/cdmi-domain";
			mime_types["cdmio"] = "application/cdmi-object";
			mime_types["cdmiq"] = "application/cdmi-queue";
			mime_types["cdx"] = "chemical/x-cdx";
			mime_types["cdxml"] = "application/vnd.chemdraw+xml";
			mime_types["cdy"] = "application/vnd.cinderella";
			mime_types["cer"] = "application/pkix-cert";
			mime_types["cfs"] = "application/x-cfs-compressed";
			mime_types["cgm"] = "image/cgm";
			mime_types["chat"] = "application/x-chat";
			mime_types["chm"] = "application/vnd.ms-htmlhelp";
			mime_types["chrt"] = "application/vnd.kde.kchart";
			mime_types["cif"] = "chemical/x-cif";
			mime_types["cii"] = "application/vnd.anser-web-certificate-issue-initiation";
			mime_types["cil"] = "application/vnd.ms-artgalry";
			mime_types["cjs"] = "application/node";
			mime_types["cla"] = "application/vnd.claymore";
			mime_types["class"] = "application/java-vm";
			mime_types["clkk"] = "application/vnd.crick.clicker.keyboard";
			mime_types["clkp"] = "application/vnd.crick.clicker.palette";
			mime_types["clkt"] = "application/vnd.crick.clicker.template";
			mime_types["clkw"] = "application/vnd.crick.clicker.wordbank";
			mime_types["clkx"] = "application/vnd.crick.clicker";
			mime_types["clp"] = "application/x-msclip";
			mime_types["cmc"] = "application/vnd.cosmocaller";
			mime_types["cmdf"] = "chemical/x-cmdf";
			mime_types["cml"] = "chemical/x-cml";
			mime_types["cmp"] = "application/vnd.yellowriver-custom-menu";
			mime_types["cmx"] = "image/x-cmx";
			mime_types["cod"] = "application/vnd.rim.cod";
			mime_types["coffee"] = "text/coffeescript";
			mime_types["litcoffee"] = "text/coffeescript";
			mime_types["conf"] = "text/plain";
			mime_types["def"] = "text/plain";
			mime_types["in"] = "text/plain";
			mime_types["ini"] = "text/plain";
			mime_types["list"] = "text/plain";
			mime_types["log"] = "text/plain";
			mime_types["text"] = "text/plain";
			mime_types["txt"] = "text/plain";
			mime_types["cpio"] = "application/x-cpio";
			mime_types["cpt"] = "application/mac-compactpro";
			mime_types["crd"] = "application/x-mscardfile";
			mime_types["crl"] = "application/pkix-crl";
			mime_types["crt"] = "application/x-x509-ca-cert";
			mime_types["der"] = "application/x-x509-ca-cert";
			mime_types["pem"] = "application/x-x509-ca-cert";
			mime_types["crx"] = "application/x-chrome-extension";
			mime_types["cryptonote"] = "application/vnd.rig.cryptonote";
			mime_types["csh"] = "application/x-csh";
			mime_types["csl"] = "application/vnd.citationstyles.style+xml";
			mime_types["csml"] = "chemical/x-csml";
			mime_types["csp"] = "application/vnd.commonspace";
			mime_types["css"] = "text/css";
			mime_types["csv"] = "text/csv";
			mime_types["cu"] = "application/cu-seeme";
			mime_types["curl"] = "text/vnd.curl";
			mime_types["cww"] = "application/prs.cww";
			mime_types["dae"] = "model/vnd.collada+xml";
			mime_types["daf"] = "application/vnd.mobius.daf";
			mime_types["dart"] = "application/vnd.dart";
			mime_types["dataless"] = "application/vnd.fdsn.seed";
			mime_types["seed"] = "application/vnd.fdsn.seed";
			mime_types["davmount"] = "application/davmount+xml";
			mime_types["dbf"] = "application/vnd.dbf";
			mime_types["dbk"] = "application/docbook+xml";
			mime_types["dcurl"] = "text/vnd.curl.dcurl";
			mime_types["dd2"] = "application/vnd.oma.dd2+xml";
			mime_types["ddd"] = "application/vnd.fujixerox.ddd";
			mime_types["ddf"] = "application/vnd.syncml.dmddf+xml";
			mime_types["dds"] = "image/vnd.ms-dds";
			mime_types["deb"] = "application/x-debian-package";
			mime_types["udeb"] = "application/x-debian-package";
			mime_types["dfac"] = "application/vnd.dreamfactory";
			mime_types["dgc"] = "application/x-dgc-compressed";
			mime_types["dis"] = "application/vnd.mobius.dis";
			mime_types["disposition-notification"] = "message/disposition-notification";
			mime_types["djv"] = "image/vnd.djvu";
			mime_types["djvu"] = "image/vnd.djvu";
			mime_types["dmg"] = "application/x-apple-diskimage";
			mime_types["dna"] = "application/vnd.dna";
			mime_types["doc"] = "application/msword";
			mime_types["dot"] = "application/msword";
			mime_types["docm"] = "application/vnd.ms-word.document.macroenabled.12";
			mime_types["docx"] = "application/vnd.openxmlformats-officedocument.wordprocessingml.document";
			mime_types["dotm"] = "application/vnd.ms-word.template.macroenabled.12";
			mime_types["dotx"] = "application/vnd.openxmlformats-officedocument.wordprocessingml.template";
			mime_types["dp"] = "application/vnd.osgi.dp";
			mime_types["dpg"] = "application/vnd.dpgraph";
			mime_types["dra"] = "audio/vnd.dra";
			mime_types["drle"] = "image/dicom-rle";
			mime_types["dsc"] = "text/prs.lines.tag";
			mime_types["dssc"] = "application/dssc+der";
			mime_types["dtb"] = "application/x-dtbook+xml";
			mime_types["dtd"] = "application/xml-dtd";
			mime_types["dts"] = "audio/vnd.dts";
			mime_types["dtshd"] = "audio/vnd.dts.hd";
			mime_types["dvb"] = "video/vnd.dvb.file";
			mime_types["dvi"] = "application/x-dvi";
			mime_types["dwd"] = "application/atsc-dwd+xml";
			mime_types["dwf"] = "model/vnd.dwf";
			mime_types["dwg"] = "image/vnd.dwg";
			mime_types["dxf"] = "image/vnd.dxf";
			mime_types["dxp"] = "application/vnd.spotfire.dxp";
			mime_types["ear"] = "application/java-archive";
			mime_types["jar"] = "application/java-archive";
			mime_types["war"] = "application/java-archive";
			mime_types["ecelp4800"] = "audio/vnd.nuera.ecelp4800";
			mime_types["ecelp7470"] = "audio/vnd.nuera.ecelp7470";
			mime_types["ecelp9600"] = "audio/vnd.nuera.ecelp9600";
			mime_types["ecma"] = "application/ecmascript";
			mime_types["es"] = "application/ecmascript";
			mime_types["edm"] = "application/vnd.novadigm.edm";
			mime_types["edx"] = "application/vnd.novadigm.edx";
			mime_types["efif"] = "application/vnd.picsel";
			mime_types["ei6"] = "application/vnd.pg.osasli";
			mime_types["emf"] = "image/emf";
			mime_types["eml"] = "message/rfc822";
			mime_types["mime"] = "message/rfc822";
			mime_types["emma"] = "application/emma+xml";
			mime_types["emotionml"] = "application/emotionml+xml";
			mime_types["emz"] = "application/x-msmetafile";
			mime_types["wmz"] = "application/x-msmetafile";
			mime_types["eol"] = "audio/vnd.digital-winds";
			mime_types["eot"] = "application/vnd.ms-fontobject";
			mime_types["epub"] = "application/epub+zip";
			mime_types["es3"] = "application/vnd.eszigno3+xml";
			mime_types["et3"] = "application/vnd.eszigno3+xml";
			mime_types["esa"] = "application/vnd.osgi.subsystem";
			mime_types["esf"] = "application/vnd.epson.esf";
			mime_types["etx"] = "text/x-setext";
			mime_types["eva"] = "application/x-eva";
			mime_types["evy"] = "application/x-envoy";
			mime_types["exi"] = "application/exi";
			mime_types["exr"] = "image/aces";
			mime_types["ext"] = "application/vnd.novadigm.ext";
			mime_types["ez"] = "application/andrew-inset";
			mime_types["ez2"] = "application/vnd.ezpix-album";
			mime_types["ez3"] = "application/vnd.ezpix-package";
			mime_types["f"] = "text/x-fortran";
			mime_types["f77"] = "text/x-fortran";
			mime_types["f90"] = "text/x-fortran";
			mime_types["for"] = "text/x-fortran";
			mime_types["f4v"] = "video/x-f4v";
			mime_types["fbs"] = "image/vnd.fastbidsheet";
			mime_types["fcdt"] = "application/vnd.adobe.formscentral.fcdt";
			mime_types["fcs"] = "application/vnd.isac.fcs";
			mime_types["fdf"] = "application/vnd.fdf";
			mime_types["fdt"] = "application/fdt+xml";
			mime_types["fe_launch"] = "application/vnd.denovo.fcselayout-link";
			mime_types["fg5"] = "application/vnd.fujitsu.oasysgp";
			mime_types["fh"] = "image/x-freehand";
			mime_types["fh4"] = "image/x-freehand";
			mime_types["fh5"] = "image/x-freehand";
			mime_types["fh7"] = "image/x-freehand";
			mime_types["fhc"] = "image/x-freehand";
			mime_types["fig"] = "application/x-xfig";
			mime_types["fits"] = "image/fits";
			mime_types["flac"] = "audio/x-flac";
			mime_types["fli"] = "video/x-fli";
			mime_types["flo"] = "application/vnd.micrografx.flo";
			mime_types["flv"] = "video/x-flv";
			mime_types["flw"] = "application/vnd.kde.kivio";
			mime_types["flx"] = "text/vnd.fmi.flexstor";
			mime_types["fly"] = "text/vnd.fly";
			mime_types["fnc"] = "application/vnd.frogans.fnc";
			mime_types["fo"] = "application/vnd.software602.filler.form+xml";
			mime_types["fpx"] = "image/vnd.fpx";
			mime_types["fsc"] = "application/vnd.fsc.weblaunch";
			mime_types["fst"] = "image/vnd.fst";
			mime_types["ftc"] = "application/vnd.fluxtime.clip";
			mime_types["fti"] = "application/vnd.anser-web-funds-transfer-initiation";
			mime_types["fvt"] = "video/vnd.fvt";
			mime_types["fxp"] = "application/vnd.adobe.fxp";
			mime_types["fxpl"] = "application/vnd.adobe.fxp";
			mime_types["fzs"] = "application/vnd.fuzzysheet";
			mime_types["g2w"] = "application/vnd.geoplan";
			mime_types["g3"] = "image/g3fax";
			mime_types["g3w"] = "application/vnd.geospace";
			mime_types["gac"] = "application/vnd.groove-account";
			mime_types["gam"] = "application/x-tads";
			mime_types["gbr"] = "application/rpki-ghostbusters";
			mime_types["gca"] = "application/x-gca-compressed";
			mime_types["gdl"] = "model/vnd.gdl";
			mime_types["gdoc"] = "application/vnd.google-apps.document";
			mime_types["geo"] = "application/vnd.dynageo";
			mime_types["geojson"] = "application/geo+json";
			mime_types["gex"] = "application/vnd.geometry-explorer";
			mime_types["gre"] = "application/vnd.geometry-explorer";
			mime_types["ggb"] = "application/vnd.geogebra.file";
			mime_types["ggt"] = "application/vnd.geogebra.tool";
			mime_types["ghf"] = "application/vnd.groove-help";
			mime_types["gif"] = "image/gif";
			mime_types["gim"] = "application/vnd.groove-identity-message";
			mime_types["glb"] = "model/gltf-binary";
			mime_types["gltf"] = "model/gltf+json";
			mime_types["gml"] = "application/gml+xml";
			mime_types["gmx"] = "application/vnd.gmx";
			mime_types["gnumeric"] = "application/x-gnumeric";
			mime_types["gph"] = "application/vnd.flographit";
			mime_types["gpx"] = "application/gpx+xml";
			mime_types["gqf"] = "application/vnd.grafeq";
			mime_types["gqs"] = "application/vnd.grafeq";
			mime_types["gram"] = "application/srgs";
			mime_types["gramps"] = "application/x-gramps-xml";
			mime_types["grv"] = "application/vnd.groove-injector";
			mime_types["grxml"] = "application/srgs+xml";
			mime_types["gsf"] = "application/x-font-ghostscript";
			mime_types["gsheet"] = "application/vnd.google-apps.spreadsheet";
			mime_types["gslides"] = "application/vnd.google-apps.presentation";
			mime_types["gtar"] = "application/x-gtar";
			mime_types["gtm"] = "application/vnd.groove-tool-message";
			mime_types["gtw"] = "model/vnd.gtw";
			mime_types["gv"] = "text/vnd.graphviz";
			mime_types["gxf"] = "application/gxf";
			mime_types["gxt"] = "application/vnd.geonext";
			mime_types["gz"] = "application/gzip";
			mime_types["h261"] = "video/h261";
			mime_types["h263"] = "video/h263";
			mime_types["h264"] = "video/h264";
			mime_types["hal"] = "application/vnd.hal+xml";
			mime_types["hbci"] = "application/vnd.hbci";
			mime_types["hbs"] = "text/x-handlebars-template";
			mime_types["hdd"] = "application/x-virtualbox-hdd";
			mime_types["hdf"] = "application/x-hdf";
			mime_types["heic"] = "image/heic";
			mime_types["heics"] = "image/heic-sequence";
			mime_types["heif"] = "image/heif";
			mime_types["heifs"] = "image/heif-sequence";
			mime_types["hej2"] = "image/hej2k";
			mime_types["held"] = "application/atsc-held+xml";
			mime_types["hjson"] = "application/hjson";
			mime_types["hlp"] = "application/winhlp";
			mime_types["hpgl"] = "application/vnd.hp-hpgl";
			mime_types["hpid"] = "application/vnd.hp-hpid";
			mime_types["hps"] = "application/vnd.hp-hps";
			mime_types["hqx"] = "application/mac-binhex40";
			mime_types["hsj2"] = "image/hsj2";
			mime_types["htc"] = "text/x-component";
			mime_types["htke"] = "application/vnd.kenameaapp";
			mime_types["htm"] = "text/html";
			mime_types["html"] = "text/html";
			mime_types["shtml"] = "text/html";
			mime_types["hvd"] = "application/vnd.yamaha.hv-dic";
			mime_types["hvp"] = "application/vnd.yamaha.hv-voice";
			mime_types["hvs"] = "application/vnd.yamaha.hv-script";
			mime_types["i2g"] = "application/vnd.intergeo";
			mime_types["icc"] = "application/vnd.iccprofile";
			mime_types["icm"] = "application/vnd.iccprofile";
			mime_types["ice"] = "x-conference/x-cooltalk";
			mime_types["ico"] = "image/x-icon";
			mime_types["ics"] = "text/calendar";
			mime_types["ifb"] = "text/calendar";
			mime_types["ief"] = "image/ief";
			mime_types["ifm"] = "application/vnd.shana.informed.formdata";
			mime_types["iges"] = "model/iges";
			mime_types["igs"] = "model/iges";
			mime_types["igl"] = "application/vnd.igloader";
			mime_types["igm"] = "application/vnd.insors.igm";
			mime_types["igx"] = "application/vnd.micrografx.igx";
			mime_types["iif"] = "application/vnd.shana.informed.interchange";
			mime_types["imp"] = "application/vnd.accpac.simply.imp";
			mime_types["ims"] = "application/vnd.ms-ims";
			mime_types["ink"] = "application/inkml+xml";
			mime_types["inkml"] = "application/inkml+xml";
			mime_types["install"] = "application/x-install-instructions";
			mime_types["iota"] = "application/vnd.astraea-software.iota";
			mime_types["ipfix"] = "application/ipfix";
			mime_types["ipk"] = "application/vnd.shana.informed.package";
			mime_types["irm"] = "application/vnd.ibm.rights-management";
			mime_types["irp"] = "application/vnd.irepository.package+xml";
			mime_types["iso"] = "application/x-iso9660-image";
			mime_types["itp"] = "application/vnd.shana.informed.formtemplate";
			mime_types["its"] = "application/its+xml";
			mime_types["ivp"] = "application/vnd.immervision-ivp";
			mime_types["ivu"] = "application/vnd.immervision-ivu";
			mime_types["jad"] = "text/vnd.sun.j2me.app-descriptor";
			mime_types["jade"] = "text/jade";
			mime_types["jam"] = "application/vnd.jam";
			mime_types["jardiff"] = "application/x-java-archive-diff";
			mime_types["java"] = "text/x-java-source";
			mime_types["jhc"] = "image/jphc";
			mime_types["jisp"] = "application/vnd.jisp";
			mime_types["jls"] = "image/jls";
			mime_types["jlt"] = "application/vnd.hp-jlyt";
			mime_types["jng"] = "image/x-jng";
			mime_types["jnlp"] = "application/x-java-jnlp-file";
			mime_types["joda"] = "application/vnd.joost.joda-archive";
			mime_types["jp2"] = "image/jp2";
			mime_types["jpg2"] = "image/jp2";
			mime_types["jpe"] = "image/jpeg";
			mime_types["jpeg"] = "image/jpeg";
			mime_types["jpg"] = "image/jpeg";
			mime_types["jpf"] = "image/jpx";
			mime_types["jpx"] = "image/jpx";
			mime_types["jpgm"] = "video/jpm";
			mime_types["jpm"] = "video/jpm";
			mime_types["jpgv"] = "video/jpeg";
			mime_types["jph"] = "image/jph";
			mime_types["js"] = "application/javascript";
			mime_types["mjs"] = "application/javascript";
			mime_types["json"] = "application/json";
			mime_types["map"] = "application/json";
			mime_types["json5"] = "application/json5";
			mime_types["jsonld"] = "application/ld+json";
			mime_types["jsonml"] = "application/jsonml+json";
			mime_types["jsx"] = "text/jsx";
			mime_types["jxr"] = "image/jxr";
			mime_types["jxra"] = "image/jxra";
			mime_types["jxrs"] = "image/jxrs";
			mime_types["jxs"] = "image/jxs";
			mime_types["jxsc"] = "image/jxsc";
			mime_types["jxsi"] = "image/jxsi";
			mime_types["jxss"] = "image/jxss";
			mime_types["kar"] = "audio/midi";
			mime_types["mid"] = "audio/midi";
			mime_types["midi"] = "audio/midi";
			mime_types["rmi"] = "audio/midi";
			mime_types["karbon"] = "application/vnd.kde.karbon";
			mime_types["kdbx"] = "application/x-keepass2";
			mime_types["key"] = "application/vnd.apple.keynote";
			mime_types["kfo"] = "application/vnd.kde.kformula";
			mime_types["kia"] = "application/vnd.kidspiration";
			mime_types["kml"] = "application/vnd.google-earth.kml+xml";
			mime_types["kmz"] = "application/vnd.google-earth.kmz";
			mime_types["kne"] = "application/vnd.kinar";
			mime_types["knp"] = "application/vnd.kinar";
			mime_types["kon"] = "application/vnd.kde.kontour";
			mime_types["kpr"] = "application/vnd.kde.kpresenter";
			mime_types["kpt"] = "application/vnd.kde.kpresenter";
			mime_types["kpxx"] = "application/vnd.ds-keypoint";
			mime_types["ksp"] = "application/vnd.kde.kspread";
			mime_types["ktr"] = "application/vnd.kahootz";
			mime_types["ktz"] = "application/vnd.kahootz";
			mime_types["ktx"] = "image/ktx";
			mime_types["ktx2"] = "image/ktx2";
			mime_types["kwd"] = "application/vnd.kde.kword";
			mime_types["kwt"] = "application/vnd.kde.kword";
			mime_types["lasxml"] = "application/vnd.las.las+xml";
			mime_types["latex"] = "application/x-latex";
			mime_types["lbd"] = "application/vnd.llamagraphics.life-balance.desktop";
			mime_types["lbe"] = "application/vnd.llamagraphics.life-balance.exchange+xml";
			mime_types["les"] = "application/vnd.hhe.lesson-player";
			mime_types["less"] = "text/less";
			mime_types["lgr"] = "application/lgr+xml";
			mime_types["lha"] = "application/x-lzh-compressed";
			mime_types["lzh"] = "application/x-lzh-compressed";
			mime_types["link66"] = "application/vnd.route66.link66+xml";
			mime_types["lnk"] = "application/x-ms-shortcut";
			mime_types["lostxml"] = "application/lost+xml";
			mime_types["lrm"] = "application/vnd.ms-lrm";
			mime_types["ltf"] = "application/vnd.frogans.ltf";
			mime_types["lua"] = "text/x-lua";
			mime_types["luac"] = "application/x-lua-bytecode";
			mime_types["lvp"] = "audio/vnd.lucent.voice";
			mime_types["lwp"] = "application/vnd.lotus-wordpro";
			mime_types["m13"] = "application/x-msmediaview";
			mime_types["m14"] = "application/x-msmediaview";
			mime_types["mvb"] = "application/x-msmediaview";
			mime_types["m1v"] = "video/mpeg";
			mime_types["m2v"] = "video/mpeg";
			mime_types["mpe"] = "video/mpeg";
			mime_types["mpeg"] = "video/mpeg";
			mime_types["mpg"] = "video/mpeg";
			mime_types["m21"] = "application/mp21";
			mime_types["mp21"] = "application/mp21";
			mime_types["m2a"] = "audio/mpeg";
			mime_types["m3a"] = "audio/mpeg";
			mime_types["mp2"] = "audio/mpeg";
			mime_types["mp2a"] = "audio/mpeg";
			mime_types["mp3"] = "audio/mpeg";
			mime_types["mpga"] = "audio/mpeg";
			mime_types["m3u"] = "audio/x-mpegurl";
			mime_types["m3u8"] = "application/vnd.apple.mpegurl";
			mime_types["m4a"] = "audio/x-m4a";
			mime_types["m4p"] = "application/mp4";
			mime_types["mp4s"] = "application/mp4";
			mime_types["m4u"] = "video/vnd.mpegurl";
			mime_types["mxu"] = "video/vnd.mpegurl";
			mime_types["m4v"] = "video/x-m4v";
			mime_types["ma"] = "application/mathematica";
			mime_types["mb"] = "application/mathematica";
			mime_types["nb"] = "application/mathematica";
			mime_types["mads"] = "application/mads+xml";
			mime_types["maei"] = "application/mmt-aei+xml";
			mime_types["mag"] = "application/vnd.ecowin.chart";
			mime_types["man"] = "text/troff";
			mime_types["me"] = "text/troff";
			mime_types["ms"] = "text/troff";
			mime_types["roff"] = "text/troff";
			mime_types["t"] = "text/troff";
			mime_types["tr"] = "text/troff";
			mime_types["markdown"] = "text/markdown";
			mime_types["md"] = "text/markdown";
			mime_types["mathml"] = "application/mathml+xml";
			mime_types["mbk"] = "application/vnd.mobius.mbk";
			mime_types["mbox"] = "application/mbox";
			mime_types["mc1"] = "application/vnd.medcalcdata";
			mime_types["mcd"] = "application/vnd.mcd";
			mime_types["mcurl"] = "text/vnd.curl.mcurl";
			mime_types["mdb"] = "application/x-msaccess";
			mime_types["mdi"] = "image/vnd.ms-modi";
			mime_types["mdx"] = "text/mdx";
			mime_types["mesh"] = "model/mesh";
			mime_types["msh"] = "model/mesh";
			mime_types["silo"] = "model/mesh";
			mime_types["meta4"] = "application/metalink4+xml";
			mime_types["metalink"] = "application/metalink+xml";
			mime_types["mets"] = "application/mets+xml";
			mime_types["mfm"] = "application/vnd.mfmp";
			mime_types["mft"] = "application/rpki-manifest";
			mime_types["mgp"] = "application/vnd.osgeo.mapguide.package";
			mime_types["mgz"] = "application/vnd.proteus.magazine";
			mime_types["mie"] = "application/x-mie";
			mime_types["mif"] = "application/vnd.mif";
			mime_types["mj2"] = "video/mj2";
			mime_types["mjp2"] = "video/mj2";
			mime_types["mk3d"] = "video/x-matroska";
			mime_types["mks"] = "video/x-matroska";
			mime_types["mkv"] = "video/x-matroska";
			mime_types["mka"] = "audio/x-matroska";
			mime_types["mkd"] = "text/x-markdown";
			mime_types["mlp"] = "application/vnd.dolby.mlp";
			mime_types["mmd"] = "application/vnd.chipnuts.karaoke-mmd";
			mime_types["mmf"] = "application/vnd.smaf";
			mime_types["mml"] = "text/mathml";
			mime_types["mmr"] = "image/vnd.fujixerox.edmics-mmr";
			mime_types["mng"] = "video/x-mng";
			mime_types["mny"] = "application/x-msmoney";
			mime_types["mobi"] = "application/x-mobipocket-ebook";
			mime_types["mods"] = "application/mods+xml";
			mime_types["mov"] = "video/quicktime";
			mime_types["qt"] = "video/quicktime";
			mime_types["movie"] = "video/x-sgi-movie";
			mime_types["mp4"] = "video/mp4";
			mime_types["mp4v"] = "video/mp4";
			mime_types["mpg4"] = "video/mp4";
			mime_types["mp4a"] = "audio/mp4";
			mime_types["mpc"] = "application/vnd.mophun.certificate";
			mime_types["mpd"] = "application/dash+xml";
			mime_types["mpkg"] = "application/vnd.apple.installer+xml";
			mime_types["mpm"] = "application/vnd.blueice.multipass";
			mime_types["mpn"] = "application/vnd.mophun.application";
			mime_types["mpp"] = "application/vnd.ms-project";
			mime_types["mpt"] = "application/vnd.ms-project";
			mime_types["mpy"] = "application/vnd.ibm.minipay";
			mime_types["mqy"] = "application/vnd.mobius.mqy";
			mime_types["mrc"] = "application/marc";
			mime_types["mrcx"] = "application/marcxml+xml";
			mime_types["mscml"] = "application/mediaservercontrol+xml";
			mime_types["mseed"] = "application/vnd.fdsn.mseed";
			mime_types["mseq"] = "application/vnd.mseq";
			mime_types["msf"] = "application/vnd.epson.msf";
			mime_types["msg"] = "application/vnd.ms-outlook";
			mime_types["msl"] = "application/vnd.mobius.msl";
			mime_types["msty"] = "application/vnd.muvee.style";
			mime_types["mtl"] = "model/mtl";
			mime_types["mts"] = "model/vnd.mts";
			mime_types["mus"] = "application/vnd.musician";
			mime_types["musd"] = "application/mmt-usd+xml";
			mime_types["musicxml"] = "application/vnd.recordare.musicxml+xml";
			mime_types["mwf"] = "application/vnd.mfer";
			mime_types["mxf"] = "application/mxf";
			mime_types["mxl"] = "application/vnd.recordare.musicxml";
			mime_types["mxmf"] = "audio/mobile-xmf";
			mime_types["mxml"] = "application/xv+xml";
			mime_types["xhvml"] = "application/xv+xml";
			mime_types["xvm"] = "application/xv+xml";
			mime_types["xvml"] = "application/xv+xml";
			mime_types["mxs"] = "application/vnd.triscape.mxs";
			mime_types["n-gage"] = "application/vnd.nokia.n-gage.symbian.install";
			mime_types["n3"] = "text/n3";
			mime_types["nbp"] = "application/vnd.wolfram.player";
			mime_types["ncx"] = "application/x-dtbncx+xml";
			mime_types["nfo"] = "text/x-nfo";
			mime_types["ngdat"] = "application/vnd.nokia.n-gage.data";
			mime_types["nitf"] = "application/vnd.nitf";
			mime_types["ntf"] = "application/vnd.nitf";
			mime_types["nlu"] = "application/vnd.neurolanguage.nlu";
			mime_types["nml"] = "application/vnd.enliven";
			mime_types["nnd"] = "application/vnd.noblenet-directory";
			mime_types["nns"] = "application/vnd.noblenet-sealer";
			mime_types["nnw"] = "application/vnd.noblenet-web";
			mime_types["npx"] = "image/vnd.net-fpx";
			mime_types["nq"] = "application/n-quads";
			mime_types["nsc"] = "application/x-conference";
			mime_types["nsf"] = "application/vnd.lotus-notes";
			mime_types["nt"] = "application/n-triples";
			mime_types["numbers"] = "application/vnd.apple.numbers";
			mime_types["nzb"] = "application/x-nzb";
			mime_types["oa2"] = "application/vnd.fujitsu.oasys2";
			mime_types["oa3"] = "application/vnd.fujitsu.oasys3";
			mime_types["oas"] = "application/vnd.fujitsu.oasys";
			mime_types["obd"] = "application/x-msbinder";
			mime_types["obgx"] = "application/vnd.openblox.game+xml";
			mime_types["obj"] = "model/obj";
			mime_types["oda"] = "application/oda";
			mime_types["odb"] = "application/vnd.oasis.opendocument.database";
			mime_types["odc"] = "application/vnd.oasis.opendocument.chart";
			mime_types["odf"] = "application/vnd.oasis.opendocument.formula";
			mime_types["odft"] = "application/vnd.oasis.opendocument.formula-template";
			mime_types["odg"] = "application/vnd.oasis.opendocument.graphics";
			mime_types["odi"] = "application/vnd.oasis.opendocument.image";
			mime_types["odm"] = "application/vnd.oasis.opendocument.text-master";
			mime_types["odp"] = "application/vnd.oasis.opendocument.presentation";
			mime_types["ods"] = "application/vnd.oasis.opendocument.spreadsheet";
			mime_types["odt"] = "application/vnd.oasis.opendocument.text";
			mime_types["oga"] = "audio/ogg";
			mime_types["ogg"] = "audio/ogg";
			mime_types["spx"] = "audio/ogg";
			mime_types["ogex"] = "model/vnd.opengex";
			mime_types["ogv"] = "video/ogg";
			mime_types["ogx"] = "application/ogg";
			mime_types["omdoc"] = "application/omdoc+xml";
			mime_types["onepkg"] = "application/onenote";
			mime_types["onetmp"] = "application/onenote";
			mime_types["onetoc"] = "application/onenote";
			mime_types["onetoc2"] = "application/onenote";
			mime_types["opf"] = "application/oebps-package+xml";
			mime_types["opml"] = "text/x-opml";
			mime_types["oprc"] = "application/vnd.palm";
			mime_types["pqa"] = "application/vnd.palm";
			mime_types["org"] = "text/x-org";
			mime_types["osf"] = "application/vnd.yamaha.openscoreformat";
			mime_types["osfpvg"] = "application/vnd.yamaha.openscoreformat.osfpvg+xml";
			mime_types["osm"] = "application/vnd.openstreetmap.data+xml";
			mime_types["otc"] = "application/vnd.oasis.opendocument.chart-template";
			mime_types["otf"] = "font/otf";
			mime_types["otg"] = "application/vnd.oasis.opendocument.graphics-template";
			mime_types["oth"] = "application/vnd.oasis.opendocument.text-web";
			mime_types["oti"] = "application/vnd.oasis.opendocument.image-template";
			mime_types["otp"] = "application/vnd.oasis.opendocument.presentation-template";
			mime_types["ots"] = "application/vnd.oasis.opendocument.spreadsheet-template";
			mime_types["ott"] = "application/vnd.oasis.opendocument.text-template";
			mime_types["ova"] = "application/x-virtualbox-ova";
			mime_types["ovf"] = "application/x-virtualbox-ovf";
			mime_types["owl"] = "application/rdf+xml";
			mime_types["rdf"] = "application/rdf+xml";
			mime_types["oxps"] = "application/oxps";
			mime_types["oxt"] = "application/vnd.openofficeorg.extension";
			mime_types["p"] = "text/x-pascal";
			mime_types["pas"] = "text/x-pascal";
			mime_types["p10"] = "application/pkcs10";
			mime_types["p12"] = "application/x-pkcs12";
			mime_types["pfx"] = "application/x-pkcs12";
			mime_types["p7b"] = "application/x-pkcs7-certificates";
			mime_types["spc"] = "application/x-pkcs7-certificates";
			mime_types["p7c"] = "application/pkcs7-mime";
			mime_types["p7m"] = "application/pkcs7-mime";
			mime_types["p7r"] = "application/x-pkcs7-certreqresp";
			mime_types["p7s"] = "application/pkcs7-signature";
			mime_types["p8"] = "application/pkcs8";
			mime_types["pac"] = "application/x-ns-proxy-autoconfig";
			mime_types["pages"] = "application/vnd.apple.pages";
			mime_types["paw"] = "application/vnd.pawaafile";
			mime_types["pbd"] = "application/vnd.powerbuilder6";
			mime_types["pbm"] = "image/x-portable-bitmap";
			mime_types["pcf"] = "application/x-font-pcf";
			mime_types["pcl"] = "application/vnd.hp-pcl";
			mime_types["pclxl"] = "application/vnd.hp-pclxl";
			mime_types["pct"] = "image/x-pict";
			mime_types["pic"] = "image/x-pict";
			mime_types["pcurl"] = "application/vnd.curl.pcurl";
			mime_types["pcx"] = "image/x-pcx";
			mime_types["pdb"] = "application/x-pilot";
			mime_types["prc"] = "application/x-pilot";
			mime_types["pde"] = "text/x-processing";
			mime_types["pdf"] = "application/pdf";
			mime_types["pfr"] = "application/font-tdpfr";
			mime_types["pgm"] = "image/x-portable-graymap";
			mime_types["pgn"] = "application/x-chess-pgn";
			mime_types["pgp"] = "application/pgp-encrypted";
			mime_types["php"] = "application/x-httpd-php";
			mime_types["pki"] = "application/pkixcmp";
			mime_types["pkipath"] = "application/pkix-pkipath";
			mime_types["pkpass"] = "application/vnd.apple.pkpass";
			mime_types["pl"] = "application/x-perl";
			mime_types["pm"] = "application/x-perl";
			mime_types["plb"] = "application/vnd.3gpp.pic-bw-large";
			mime_types["plc"] = "application/vnd.mobius.plc";
			mime_types["plf"] = "application/vnd.pocketlearn";
			mime_types["pls"] = "application/pls+xml";
			mime_types["pml"] = "application/vnd.ctc-posml";
			mime_types["png"] = "image/png";
			mime_types["pnm"] = "image/x-portable-anymap";
			mime_types["portpkg"] = "application/vnd.macports.portpkg";
			mime_types["pot"] = "application/vnd.ms-powerpoint";
			mime_types["pps"] = "application/vnd.ms-powerpoint";
			mime_types["ppt"] = "application/vnd.ms-powerpoint";
			mime_types["potm"] = "application/vnd.ms-powerpoint.template.macroenabled.12";
			mime_types["potx"] = "application/vnd.openxmlformats-officedocument.presentationml.template";
			mime_types["ppam"] = "application/vnd.ms-powerpoint.addin.macroenabled.12";
			mime_types["ppd"] = "application/vnd.cups-ppd";
			mime_types["ppm"] = "image/x-portable-pixmap";
			mime_types["ppsm"] = "application/vnd.ms-powerpoint.slideshow.macroenabled.12";
			mime_types["ppsx"] = "application/vnd.openxmlformats-officedocument.presentationml.slideshow";
			mime_types["pptm"] = "application/vnd.ms-powerpoint.presentation.macroenabled.12";
			mime_types["pptx"] = "application/vnd.openxmlformats-officedocument.presentationml.presentation";
			mime_types["pre"] = "application/vnd.lotus-freelance";
			mime_types["prf"] = "application/pics-rules";
			mime_types["provx"] = "application/provenance+xml";
			mime_types["psb"] = "application/vnd.3gpp.pic-bw-small";
			mime_types["psd"] = "image/vnd.adobe.photoshop";
			mime_types["psf"] = "application/x-font-linux-psf";
			mime_types["pskcxml"] = "application/pskc+xml";
			mime_types["pti"] = "image/prs.pti";
			mime_types["ptid"] = "application/vnd.pvi.ptid1";
			mime_types["pub"] = "application/x-mspublisher";
			mime_types["pvb"] = "application/vnd.3gpp.pic-bw-var";
			mime_types["pwn"] = "application/vnd.3m.post-it-notes";
			mime_types["pya"] = "audio/vnd.ms-playready.media.pya";
			mime_types["pyv"] = "video/vnd.ms-playready.media.pyv";
			mime_types["qam"] = "application/vnd.epson.quickanime";
			mime_types["qbo"] = "application/vnd.intu.qbo";
			mime_types["qfx"] = "application/vnd.intu.qfx";
			mime_types["qps"] = "application/vnd.publishare-delta-tree";
			mime_types["qwd"] = "application/vnd.quark.quarkxpress";
			mime_types["qwt"] = "application/vnd.quark.quarkxpress";
			mime_types["qxb"] = "application/vnd.quark.quarkxpress";
			mime_types["qxd"] = "application/vnd.quark.quarkxpress";
			mime_types["qxl"] = "application/vnd.quark.quarkxpress";
			mime_types["qxt"] = "application/vnd.quark.quarkxpress";
			mime_types["ra"] = "audio/x-realaudio";
			mime_types["ram"] = "audio/x-pn-realaudio";
			mime_types["raml"] = "application/raml+yaml";
			mime_types["rapd"] = "application/route-apd+xml";
			mime_types["rar"] = "application/x-rar-compressed";
			mime_types["ras"] = "image/x-cmu-raster";
			mime_types["rcprofile"] = "application/vnd.ipunplugged.rcprofile";
			mime_types["rdz"] = "application/vnd.data-vision.rdz";
			mime_types["relo"] = "application/p2p-overlay+xml";
			mime_types["rep"] = "application/vnd.businessobjects";
			mime_types["res"] = "application/x-dtbresource+xml";
			mime_types["rgb"] = "image/x-rgb";
			mime_types["rif"] = "application/reginfo+xml";
			mime_types["rip"] = "audio/vnd.rip";
			mime_types["ris"] = "application/x-research-info-systems";
			mime_types["rl"] = "application/resource-lists+xml";
			mime_types["rlc"] = "image/vnd.fujixerox.edmics-rlc";
			mime_types["rld"] = "application/resource-lists-diff+xml";
			mime_types["rm"] = "application/vnd.rn-realmedia";
			mime_types["rmp"] = "audio/x-pn-realaudio-plugin";
			mime_types["rms"] = "application/vnd.jcp.javame.midlet-rms";
			mime_types["rmvb"] = "application/vnd.rn-realmedia-vbr";
			mime_types["rnc"] = "application/relax-ng-compact-syntax";
			mime_types["rng"] = "application/xml";
			mime_types["xsd"] = "application/xml";
			mime_types["roa"] = "application/rpki-roa";
			mime_types["rp9"] = "application/vnd.cloanto.rp9";
			mime_types["rpm"] = "application/x-redhat-package-manager";
			mime_types["rpss"] = "application/vnd.nokia.radio-presets";
			mime_types["rpst"] = "application/vnd.nokia.radio-preset";
			mime_types["rq"] = "application/sparql-query";
			mime_types["rs"] = "application/rls-services+xml";
			mime_types["rsat"] = "application/atsc-rsat+xml";
			mime_types["rsd"] = "application/rsd+xml";
			mime_types["rsheet"] = "application/urc-ressheet+xml";
			mime_types["rss"] = "application/rss+xml";
			mime_types["rtf"] = "text/rtf";
			mime_types["rtx"] = "text/richtext";
			mime_types["run"] = "application/x-makeself";
			mime_types["rusd"] = "application/route-usd+xml";
			mime_types["s3m"] = "audio/s3m";
			mime_types["saf"] = "application/vnd.yamaha.smaf-audio";
			mime_types["sass"] = "text/x-sass";
			mime_types["sbml"] = "application/sbml+xml";
			mime_types["sc"] = "application/vnd.ibm.secure-container";
			mime_types["scd"] = "application/x-msschedule";
			mime_types["scm"] = "application/vnd.lotus-screencam";
			mime_types["scq"] = "application/scvp-cv-request";
			mime_types["scs"] = "application/scvp-cv-response";
			mime_types["scss"] = "text/x-scss";
			mime_types["scurl"] = "text/vnd.curl.scurl";
			mime_types["sda"] = "application/vnd.stardivision.draw";
			mime_types["sdc"] = "application/vnd.stardivision.calc";
			mime_types["sdd"] = "application/vnd.stardivision.impress";
			mime_types["sdkd"] = "application/vnd.solent.sdkm+xml";
			mime_types["sdkm"] = "application/vnd.solent.sdkm+xml";
			mime_types["sdp"] = "application/sdp";
			mime_types["sdw"] = "application/vnd.stardivision.writer";
			mime_types["vor"] = "application/vnd.stardivision.writer";
			mime_types["sea"] = "application/x-sea";
			mime_types["see"] = "application/vnd.seemail";
			mime_types["sema"] = "application/vnd.sema";
			mime_types["semd"] = "application/vnd.semd";
			mime_types["semf"] = "application/vnd.semf";
			mime_types["senmlx"] = "application/senml+xml";
			mime_types["sensmlx"] = "application/sensml+xml";
			mime_types["ser"] = "application/java-serialized-object";
			mime_types["setpay"] = "application/set-payment-initiation";
			mime_types["setreg"] = "application/set-registration-initiation";
			mime_types["sfd-hdstx"] = "application/vnd.hydrostatix.sof-data";
			mime_types["sfs"] = "application/vnd.spotfire.sfs";
			mime_types["sfv"] = "text/x-sfv";
			mime_types["sgi"] = "image/sgi";
			mime_types["sgl"] = "application/vnd.stardivision.writer-global";
			mime_types["sgm"] = "text/sgml";
			mime_types["sgml"] = "text/sgml";
			mime_types["sh"] = "application/x-sh";
			mime_types["shar"] = "application/x-shar";
			mime_types["shex"] = "text/shex";
			mime_types["shf"] = "application/shf+xml";
			mime_types["sid"] = "image/x-mrsid-image";
			mime_types["sieve"] = "application/sieve";
			mime_types["siv"] = "application/sieve";
			mime_types["sil"] = "audio/silk";
			mime_types["sis"] = "application/vnd.symbian.install";
			mime_types["sisx"] = "application/vnd.symbian.install";
			mime_types["sit"] = "application/x-stuffit";
			mime_types["sitx"] = "application/x-stuffitx";
			mime_types["skd"] = "application/vnd.koan";
			mime_types["skm"] = "application/vnd.koan";
			mime_types["skp"] = "application/vnd.koan";
			mime_types["skt"] = "application/vnd.koan";
			mime_types["sldm"] = "application/vnd.ms-powerpoint.slide.macroenabled.12";
			mime_types["sldx"] = "application/vnd.openxmlformats-officedocument.presentationml.slide";
			mime_types["slim"] = "text/slim";
			mime_types["slm"] = "text/slim";
			mime_types["sls"] = "application/route-s-tsid+xml";
			mime_types["slt"] = "application/vnd.epson.salt";
			mime_types["sm"] = "application/vnd.stepmania.stepchart";
			mime_types["smf"] = "application/vnd.stardivision.math";
			mime_types["smi"] = "application/smil+xml";
			mime_types["smil"] = "application/smil+xml";
			mime_types["smv"] = "video/x-smv";
			mime_types["smzip"] = "application/vnd.stepmania.package";
			mime_types["snf"] = "application/x-font-snf";
			mime_types["spdx"] = "text/spdx";
			mime_types["spf"] = "application/vnd.yamaha.smaf-phrase";
			mime_types["spl"] = "application/x-futuresplash";
			mime_types["spot"] = "text/vnd.in3d.spot";
			mime_types["spp"] = "application/scvp-vp-response";
			mime_types["spq"] = "application/scvp-vp-request";
			mime_types["sql"] = "application/x-sql";
			mime_types["src"] = "application/x-wais-source";
			mime_types["srt"] = "application/x-subrip";
			mime_types["sru"] = "application/sru+xml";
			mime_types["srx"] = "application/sparql-results+xml";
			mime_types["ssdl"] = "application/ssdl+xml";
			mime_types["sse"] = "application/vnd.kodak-descriptor";
			mime_types["ssf"] = "application/vnd.epson.ssf";
			mime_types["ssml"] = "application/ssml+xml";
			mime_types["st"] = "application/vnd.sailingtracker.track";
			mime_types["stc"] = "application/vnd.sun.xml.calc.template";
			mime_types["std"] = "application/vnd.sun.xml.draw.template";
			mime_types["stf"] = "application/vnd.wt.stf";
			mime_types["sti"] = "application/vnd.sun.xml.impress.template";
			mime_types["stk"] = "application/hyperstudio";
			mime_types["stl"] = "model/stl";
			mime_types["str"] = "application/vnd.pg.format";
			mime_types["stw"] = "application/vnd.sun.xml.writer.template";
			mime_types["styl"] = "text/stylus";
			mime_types["stylus"] = "text/stylus";
			mime_types["sub"] = "text/vnd.dvb.subtitle";
			mime_types["sus"] = "application/vnd.sus-calendar";
			mime_types["susp"] = "application/vnd.sus-calendar";
			mime_types["sv4cpio"] = "application/x-sv4cpio";
			mime_types["sv4crc"] = "application/x-sv4crc";
			mime_types["svc"] = "application/vnd.dvb.service";
			mime_types["svd"] = "application/vnd.svd";
			mime_types["svg"] = "image/svg+xml";
			mime_types["svgz"] = "image/svg+xml";
			mime_types["swf"] = "application/x-shockwave-flash";
			mime_types["swi"] = "application/vnd.aristanetworks.swi";
			mime_types["swidtag"] = "application/swid+xml";
			mime_types["sxc"] = "application/vnd.sun.xml.calc";
			mime_types["sxd"] = "application/vnd.sun.xml.draw";
			mime_types["sxg"] = "application/vnd.sun.xml.writer.global";
			mime_types["sxi"] = "application/vnd.sun.xml.impress";
			mime_types["sxm"] = "application/vnd.sun.xml.math";
			mime_types["sxw"] = "application/vnd.sun.xml.writer";
			mime_types["t3"] = "application/x-t3vm-image";
			mime_types["t38"] = "image/t38";
			mime_types["taglet"] = "application/vnd.mynfc";
			mime_types["tao"] = "application/vnd.tao.intent-module-archive";
			mime_types["tap"] = "image/vnd.tencent.tap";
			mime_types["tar"] = "application/x-tar";
			mime_types["tcap"] = "application/vnd.3gpp2.tcap";
			mime_types["tcl"] = "application/x-tcl";
			mime_types["tk"] = "application/x-tcl";
			mime_types["td"] = "application/urc-targetdesc+xml";
			mime_types["teacher"] = "application/vnd.smart.teacher";
			mime_types["tei"] = "application/tei+xml";
			mime_types["teicorpus"] = "application/tei+xml";
			mime_types["tex"] = "application/x-tex";
			mime_types["texi"] = "application/x-texinfo";
			mime_types["texinfo"] = "application/x-texinfo";
			mime_types["tfi"] = "application/thraud+xml";
			mime_types["tfm"] = "application/x-tex-tfm";
			mime_types["tfx"] = "image/tiff-fx";
			mime_types["tga"] = "image/x-tga";
			mime_types["thmx"] = "application/vnd.ms-officetheme";
			mime_types["tif"] = "image/tiff";
			mime_types["tiff"] = "image/tiff";
			mime_types["tmo"] = "application/vnd.tmobile-livetv";
			mime_types["toml"] = "application/toml";
			mime_types["torrent"] = "application/x-bittorrent";
			mime_types["tpl"] = "application/vnd.groove-tool-template";
			mime_types["tpt"] = "application/vnd.trid.tpt";
			mime_types["tra"] = "application/vnd.trueapp";
			mime_types["trm"] = "application/x-msterminal";
			mime_types["ts"] = "video/mp2t";
			mime_types["tsd"] = "application/timestamped-data";
			mime_types["tsv"] = "text/tab-separated-values";
			mime_types["ttc"] = "font/collection";
			mime_types["ttf"] = "font/ttf";
			mime_types["ttl"] = "text/turtle";
			mime_types["ttml"] = "application/ttml+xml";
			mime_types["twd"] = "application/vnd.simtech-mindmapper";
			mime_types["twds"] = "application/vnd.simtech-mindmapper";
			mime_types["txd"] = "application/vnd.genomatix.tuxedo";
			mime_types["txf"] = "application/vnd.mobius.txf";
			mime_types["u8dsn"] = "message/global-delivery-status";
			mime_types["u8hdr"] = "message/global-headers";
			mime_types["u8mdn"] = "message/global-disposition-notification";
			mime_types["u8msg"] = "message/global";
			mime_types["ubj"] = "application/ubjson";
			mime_types["ufd"] = "application/vnd.ufdl";
			mime_types["ufdl"] = "application/vnd.ufdl";
			mime_types["ulx"] = "application/x-glulx";
			mime_types["umj"] = "application/vnd.umajin";
			mime_types["unityweb"] = "application/vnd.unity";
			mime_types["uoml"] = "application/vnd.uoml+xml";
			mime_types["uri"] = "text/uri-list";
			mime_types["uris"] = "text/uri-list";
			mime_types["urls"] = "text/uri-list";
			mime_types["usdz"] = "model/vnd.usdz+zip";
			mime_types["ustar"] = "application/x-ustar";
			mime_types["utz"] = "application/vnd.uiq.theme";
			mime_types["uu"] = "text/x-uuencode";
			mime_types["uva"] = "audio/vnd.dece.audio";
			mime_types["uvva"] = "audio/vnd.dece.audio";
			mime_types["uvd"] = "application/vnd.dece.data";
			mime_types["uvf"] = "application/vnd.dece.data";
			mime_types["uvvd"] = "application/vnd.dece.data";
			mime_types["uvvf"] = "application/vnd.dece.data";
			mime_types["uvg"] = "image/vnd.dece.graphic";
			mime_types["uvi"] = "image/vnd.dece.graphic";
			mime_types["uvvg"] = "image/vnd.dece.graphic";
			mime_types["uvvi"] = "image/vnd.dece.graphic";
			mime_types["uvh"] = "video/vnd.dece.hd";
			mime_types["uvvh"] = "video/vnd.dece.hd";
			mime_types["uvm"] = "video/vnd.dece.mobile";
			mime_types["uvvm"] = "video/vnd.dece.mobile";
			mime_types["uvp"] = "video/vnd.dece.pd";
			mime_types["uvvp"] = "video/vnd.dece.pd";
			mime_types["uvs"] = "video/vnd.dece.sd";
			mime_types["uvvs"] = "video/vnd.dece.sd";
			mime_types["uvt"] = "application/vnd.dece.ttml+xml";
			mime_types["uvvt"] = "application/vnd.dece.ttml+xml";
			mime_types["uvu"] = "video/vnd.uvvu.mp4";
			mime_types["uvvu"] = "video/vnd.uvvu.mp4";
			mime_types["uvv"] = "video/vnd.dece.video";
			mime_types["uvvv"] = "video/vnd.dece.video";
			mime_types["uvvx"] = "application/vnd.dece.unspecified";
			mime_types["uvx"] = "application/vnd.dece.unspecified";
			mime_types["uvvz"] = "application/vnd.dece.zip";
			mime_types["uvz"] = "application/vnd.dece.zip";
			mime_types["vbox"] = "application/x-virtualbox-vbox";
			mime_types["vbox-extpack"] = "application/x-virtualbox-vbox-extpack";
			mime_types["vcard"] = "text/vcard";
			mime_types["vcd"] = "application/x-cdlink";
			mime_types["vcf"] = "text/x-vcard";
			mime_types["vcg"] = "application/vnd.groove-vcard";
			mime_types["vcs"] = "text/x-vcalendar";
			mime_types["vcx"] = "application/vnd.vcx";
			mime_types["vdi"] = "application/x-virtualbox-vdi";
			mime_types["vhd"] = "application/x-virtualbox-vhd";
			mime_types["vis"] = "application/vnd.visionary";
			mime_types["viv"] = "video/vnd.vivo";
			mime_types["vmdk"] = "application/x-virtualbox-vmdk";
			mime_types["vob"] = "video/x-ms-vob";
			mime_types["vrml"] = "model/vrml";
			mime_types["wrl"] = "model/vrml";
			mime_types["vsd"] = "application/vnd.visio";
			mime_types["vss"] = "application/vnd.visio";
			mime_types["vst"] = "application/vnd.visio";
			mime_types["vsw"] = "application/vnd.visio";
			mime_types["vsf"] = "application/vnd.vsf";
			mime_types["vtf"] = "image/vnd.valve.source.texture";
			mime_types["vtt"] = "text/vtt";
			mime_types["vtu"] = "model/vnd.vtu";
			mime_types["vxml"] = "application/voicexml+xml";
			mime_types["wad"] = "application/x-doom";
			mime_types["wadl"] = "application/vnd.sun.wadl+xml";
			mime_types["wasm"] = "application/wasm";
			mime_types["wav"] = "audio/x-wav";
			mime_types["wax"] = "audio/x-ms-wax";
			mime_types["wbmp"] = "image/vnd.wap.wbmp";
			mime_types["wbs"] = "application/vnd.criticaltools.wbs+xml";
			mime_types["wbxml"] = "application/vnd.wap.wbxml";
			mime_types["wcm"] = "application/vnd.ms-works";
			mime_types["wdb"] = "application/vnd.ms-works";
			mime_types["wks"] = "application/vnd.ms-works";
			mime_types["wps"] = "application/vnd.ms-works";
			mime_types["wdp"] = "image/vnd.ms-photo";
			mime_types["weba"] = "audio/webm";
			mime_types["webapp"] = "application/x-web-app-manifest+json";
			mime_types["webm"] = "video/webm";
			mime_types["webmanifest"] = "application/manifest+json";
			mime_types["webp"] = "image/webp";
			mime_types["wg"] = "application/vnd.pmi.widget";
			mime_types["wgt"] = "application/widget";
			mime_types["wm"] = "video/x-ms-wm";
			mime_types["wma"] = "audio/x-ms-wma";
			mime_types["wmd"] = "application/x-ms-wmd";
			mime_types["wmf"] = "image/wmf";
			mime_types["wml"] = "text/vnd.wap.wml";
			mime_types["wmlc"] = "application/vnd.wap.wmlc";
			mime_types["wmls"] = "text/vnd.wap.wmlscript";
			mime_types["wmlsc"] = "application/vnd.wap.wmlscriptc";
			mime_types["wmv"] = "video/x-ms-wmv";
			mime_types["wmx"] = "video/x-ms-wmx";
			mime_types["woff"] = "font/woff";
			mime_types["woff2"] = "font/woff2";
			mime_types["wpd"] = "application/vnd.wordperfect";
			mime_types["wpl"] = "application/vnd.ms-wpl";
			mime_types["wqd"] = "application/vnd.wqd";
			mime_types["wri"] = "application/x-mswrite";
			mime_types["wsc"] = "message/vnd.wfa.wsc";
			mime_types["wsdl"] = "application/wsdl+xml";
			mime_types["wspolicy"] = "application/wspolicy+xml";
			mime_types["wtb"] = "application/vnd.webturbo";
			mime_types["wvx"] = "video/x-ms-wvx";
			mime_types["x3d"] = "model/x3d+xml";
			mime_types["x3dz"] = "model/x3d+xml";
			mime_types["x3db"] = "model/x3d+fastinfoset";
			mime_types["x3dbz"] = "model/x3d+binary";
			mime_types["x3dv"] = "model/x3d-vrml";
			mime_types["x3dvz"] = "model/x3d+vrml";
			mime_types["x_b"] = "model/vnd.parasolid.transmit.binary";
			mime_types["x_t"] = "model/vnd.parasolid.transmit.text";
			mime_types["xaml"] = "application/xaml+xml";
			mime_types["xap"] = "application/x-silverlight-app";
			mime_types["xar"] = "application/vnd.xara";
			mime_types["xav"] = "application/xcap-att+xml";
			mime_types["xbap"] = "application/x-ms-xbap";
			mime_types["xbd"] = "application/vnd.fujixerox.docuworks.binder";
			mime_types["xbm"] = "image/x-xbitmap";
			mime_types["xca"] = "application/xcap-caps+xml";
			mime_types["xcs"] = "application/calendar+xml";
			mime_types["xdf"] = "application/xcap-diff+xml";
			mime_types["xdm"] = "application/vnd.syncml.dm+xml";
			mime_types["xdp"] = "application/vnd.adobe.xdp+xml";
			mime_types["xdssc"] = "application/dssc+xml";
			mime_types["xdw"] = "application/vnd.fujixerox.docuworks";
			mime_types["xel"] = "application/xcap-el+xml";
			mime_types["xenc"] = "application/xenc+xml";
			mime_types["xer"] = "application/xcap-error+xml";
			mime_types["xfdf"] = "application/vnd.adobe.xfdf";
			mime_types["xfdl"] = "application/vnd.xfdl";
			mime_types["xht"] = "application/xhtml+xml";
			mime_types["xhtml"] = "application/xhtml+xml";
			mime_types["xif"] = "image/vnd.xiff";
			mime_types["xla"] = "application/vnd.ms-excel";
			mime_types["xlc"] = "application/vnd.ms-excel";
			mime_types["xlm"] = "application/vnd.ms-excel";
			mime_types["xls"] = "application/vnd.ms-excel";
			mime_types["xlt"] = "application/vnd.ms-excel";
			mime_types["xlw"] = "application/vnd.ms-excel";
			mime_types["xlam"] = "application/vnd.ms-excel.addin.macroenabled.12";
			mime_types["xlf"] = "application/xliff+xml";
			mime_types["xlsb"] = "application/vnd.ms-excel.sheet.binary.macroenabled.12";
			mime_types["xlsm"] = "application/vnd.ms-excel.sheet.macroenabled.12";
			mime_types["xlsx"] = "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet";
			mime_types["xltm"] = "application/vnd.ms-excel.template.macroenabled.12";
			mime_types["xltx"] = "application/vnd.openxmlformats-officedocument.spreadsheetml.template";
			mime_types["xm"] = "audio/xm";
			mime_types["xml"] = "text/xml";
			mime_types["xns"] = "application/xcap-ns+xml";
			mime_types["xo"] = "application/vnd.olpc-sugar";
			mime_types["xop"] = "application/xop+xml";
			mime_types["xpi"] = "application/x-xpinstall";
			mime_types["xpl"] = "application/xproc+xml";
			mime_types["xpm"] = "image/x-xpixmap";
			mime_types["xpr"] = "application/vnd.is-xpr";
			mime_types["xps"] = "application/vnd.ms-xpsdocument";
			mime_types["xpw"] = "application/vnd.intercon.formnet";
			mime_types["xpx"] = "application/vnd.intercon.formnet";
			mime_types["xsl"] = "application/xslt+xml";
			mime_types["xslt"] = "application/xslt+xml";
			mime_types["xsm"] = "application/vnd.syncml+xml";
			mime_types["xspf"] = "application/xspf+xml";
			mime_types["xul"] = "application/vnd.mozilla.xul+xml";
			mime_types["xwd"] = "image/x-xwindowdump";
			mime_types["xyz"] = "chemical/x-xyz";
			mime_types["xz"] = "application/x-xz";
			mime_types["yaml"] = "text/yaml";
			mime_types["yml"] = "text/yaml";
			mime_types["yang"] = "application/yang";
			mime_types["yin"] = "application/yin+xml";
			mime_types["ymp"] = "text/x-suse-ymp";
			mime_types["z1"] = "application/x-zmachine";
			mime_types["z2"] = "application/x-zmachine";
			mime_types["z3"] = "application/x-zmachine";
			mime_types["z4"] = "application/x-zmachine";
			mime_types["z5"] = "application/x-zmachine";
			mime_types["z6"] = "application/x-zmachine";
			mime_types["z7"] = "application/x-zmachine";
			mime_types["z8"] = "application/x-zmachine";
			mime_types["zaz"] = "application/vnd.zzazz.deck+xml";
			mime_types["zip"] = "application/zip";
			mime_types["zir"] = "application/vnd.zul";
			mime_types["zirz"] = "application/vnd.zul";
			mime_types["zmm"] = "application/vnd.handheld-entertainment+xml";
		}
		std::map<std::string, std::string>::const_iterator it = mime_types.find(ext);
		if (it != mime_types.end()) {
			return (it->second);
		}
		return "";
	}
}
