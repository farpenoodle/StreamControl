(function() {

  var iso = {};

  // global on the server, window in the browser
  var root = this,
    previous_iso = root.iso;

  if (typeof module !== 'undefined' && module.exports) {
    module.exports = iso;
  } else {
    root.iso = iso;
  }

  iso.noConflict = function() {
    root.iso = previous_iso;
    return iso;
  };

  iso.version = '0.1';

  iso.countries = {
  "ad": {
    "value": "ad",
    "name": "andorra",
    "names": [
      "andorre",
      "andorra"
    ],
    "region": "europe",
    "subregion": "southern europe",
    "currency": "eur",
    "alpha2": "ad",
    "alpha3": "and",
    "ioc": "and",
    "number": "020",
    "tel": "376",
    "latitude": "42 30 n",
    "longitude": "1 30 e",
    "un": "ad"
  },
  "ae": {
    "value": "ae",
    "name": "united arab emirates",
    "names": [
      "united arab emirates",
      "vereinigte arabische emirate",
      "émirats arabes unis",
      "emiratos árabes unidos"
    ],
    "region": "asia",
    "subregion": "western asia",
    "currency": "aed",
    "alpha2": "ae",
    "alpha3": "are",
    "ioc": "uae",
    "number": "784",
    "tel": "971",
    "latitude": "24 00 n",
    "longitude": "54 00 e",
    "un": "ae"
  },
  "af": {
    "value": "af",
    "name": "afghanistan",
    "names": [
      "afghanistan",
      "afganistán"
    ],
    "region": "asia",
    "subregion": "southern asia",
    "currency": "afn",
    "alpha2": "af",
    "alpha3": "afg",
    "ioc": "afg",
    "number": "004",
    "tel": "93",
    "latitude": "33 00 n",
    "longitude": "65 00 e",
    "un": "af"
  },
  "ag": {
    "value": "ag",
    "name": "antigua and barbuda",
    "names": [
      "antigua and barbuda",
      "antigua und barbuda",
      "antigua et barbuda",
      "antigua y barbuda"
    ],
    "region": "americas",
    "subregion": "caribbean",
    "currency": "xcd",
    "alpha2": "ag",
    "alpha3": "atg",
    "ioc": "ant",
    "number": "028",
    "tel": "1",
    "latitude": "17 03 n",
    "longitude": "61 48 w",
    "un": "ag"
  },
  "ai": {
    "value": "ai",
    "name": "anguilla",
    "names": [
      "anguilla"
    ],
    "region": "americas",
    "subregion": "caribbean",
    "currency": "xcd",
    "alpha2": "ai",
    "alpha3": "aia",
    "ioc": null,
    "number": "660",
    "tel": "1",
    "latitude": "18 15 n",
    "longitude": "63 10 w",
    "un": "ai"
  },
  "al": {
    "value": "al",
    "name": "albania",
    "names": [
      "albania",
      "albanien",
      "albanie"
    ],
    "region": "europe",
    "subregion": "southern europe",
    "currency": "all",
    "alpha2": "al",
    "alpha3": "alb",
    "ioc": "alb",
    "number": "008",
    "tel": "355",
    "latitude": "41 00 n",
    "longitude": "20 00 e",
    "un": "al"
  },
  "am": {
    "value": "am",
    "name": "armenia",
    "names": [
      "armenia",
      "armenien",
      "arménie"
    ],
    "region": "asia",
    "subregion": "western asia",
    "currency": "amd",
    "alpha2": "am",
    "alpha3": "arm",
    "ioc": "arm",
    "number": "051",
    "tel": "374",
    "latitude": "40 00 n",
    "longitude": "45 00 e",
    "un": "am"
  },
  "an": {
    "value": "an",
    "name": "netherlands antilles",
    "names": [
      "netherlands antilles",
      "niederländische antillen",
      "antilles néerlandaises",
      "antillas holandesas"
    ],
    "region": "americas",
    "subregion": "caribbean",
    "currency": "ang",
    "alpha2": "an",
    "alpha3": "ant",
    "ioc": "aho",
    "number": "530",
    "tel": "599",
    "latitude": "",
    "longitude": "",
    "un": "an"
  },
  "ao": {
    "value": "ao",
    "name": "angola",
    "names": [
      "angola"
    ],
    "region": "africa",
    "subregion": "middle africa",
    "currency": "aoa",
    "alpha2": "ao",
    "alpha3": "ago",
    "ioc": "ang",
    "number": "024",
    "tel": "244",
    "latitude": "12 30 s",
    "longitude": "18 30 e",
    "un": "ao"
  },
  "aq": {
    "value": "aq",
    "name": "antarctica",
    "names": [
      "antarctica",
      "antarktis",
      "antarctique",
      "antártida"
    ],
    "region": "",
    "subregion": "",
    "currency": null,
    "alpha2": "aq",
    "alpha3": "ata",
    "ioc": null,
    "number": "010",
    "tel": "672",
    "latitude": "90 00 s",
    "longitude": "0 00 e",
    "un": "aq"
  },
  "ar": {
    "value": "ar",
    "name": "argentina",
    "names": [
      "argentina",
      "argentinien",
      "argentine"
    ],
    "region": "americas",
    "subregion": "south america",
    "currency": "ars",
    "alpha2": "ar",
    "alpha3": "arg",
    "ioc": "arg",
    "number": "032",
    "tel": "54",
    "latitude": "34 00 s",
    "longitude": "64 00 w",
    "un": "ar"
  },
  "as": {
    "value": "as",
    "name": "american samoa",
    "names": [
      "american samoa",
      "amerikanisch-samoa",
      "samoa américaines",
      "samoa americana"
    ],
    "region": "oceania",
    "subregion": "polynesia",
    "currency": "usd",
    "alpha2": "as",
    "alpha3": "asm",
    "ioc": "asa",
    "number": "016",
    "tel": "1",
    "latitude": "14 20 s",
    "longitude": "170 00 w",
    "un": "as"
  },
  "at": {
    "value": "at",
    "name": "austria",
    "names": [
      "österreich",
      "autriche",
      "austria"
    ],
    "region": "europe",
    "subregion": "western europe",
    "currency": "eur",
    "alpha2": "at",
    "alpha3": "aut",
    "ioc": "aut",
    "number": "040",
    "tel": "43",
    "latitude": "47 20 n",
    "longitude": "13 20 e",
    "un": "at"
  },
  "au": {
    "value": "au",
    "name": "australia",
    "names": [
      "australien",
      "australie",
      "australia"
    ],
    "region": "oceania",
    "subregion": "australia and new zealand",
    "currency": "aud",
    "alpha2": "au",
    "alpha3": "aus",
    "ioc": "aus",
    "number": "036",
    "tel": "61",
    "latitude": "27 00 s",
    "longitude": "133 00 e",
    "un": "au"
  },
  "aw": {
    "value": "aw",
    "name": "aruba",
    "names": [
      "aruba"
    ],
    "region": "americas",
    "subregion": "caribbean",
    "currency": "awg",
    "alpha2": "aw",
    "alpha3": "abw",
    "ioc": "aru",
    "number": "533",
    "tel": "297",
    "latitude": "12 30 n",
    "longitude": "69 58 w",
    "un": "aw"
  },
  "ax": {
    "value": "ax",
    "name": "åland islands",
    "names": [
      "åland islands"
    ],
    "region": "europe",
    "subregion": "northern europe",
    "currency": null,
    "alpha2": "ax",
    "alpha3": "ala",
    "ioc": null,
    "number": "248",
    "tel": "358",
    "latitude": "",
    "longitude": "",
    "un": null
  },
  "az": {
    "value": "az",
    "name": "azerbaijan",
    "names": [
      "azerbaijan",
      "aserbaidschan",
      "azerbaïdjan",
      "azerbaiyán"
    ],
    "region": "asia",
    "subregion": "western asia",
    "currency": "azn",
    "alpha2": "az",
    "alpha3": "aze",
    "ioc": "aze",
    "number": "031",
    "tel": "994",
    "latitude": "40 30 n",
    "longitude": "47 30 e",
    "un": "az"
  },
  "ba": {
    "value": "ba",
    "name": "bosnia and herzegovina",
    "names": [
      "bosnia and herzegovina",
      "bosnien und herzegowina",
      "bosnie et herzégovine",
      "bosnia y herzegovina"
    ],
    "region": "europe",
    "subregion": "southern europe",
    "currency": "bam",
    "alpha2": "ba",
    "alpha3": "bih",
    "ioc": "bih",
    "number": "070",
    "tel": "387",
    "latitude": "44 00 n",
    "longitude": "18 00 e",
    "un": "ba"
  },
  "bb": {
    "value": "bb",
    "name": "barbados",
    "names": [
      "barbade",
      "barbados"
    ],
    "region": "americas",
    "subregion": "caribbean",
    "currency": "bbd",
    "alpha2": "bb",
    "alpha3": "brb",
    "ioc": "bar",
    "number": "052",
    "tel": "1",
    "latitude": "13 10 n",
    "longitude": "59 32 w",
    "un": "bb"
  },
  "bd": {
    "value": "bd",
    "name": "bangladesh",
    "names": [
      "bangladesh",
      "bangladesch"
    ],
    "region": "asia",
    "subregion": "southern asia",
    "currency": "btd",
    "alpha2": "bd",
    "alpha3": "bgd",
    "ioc": "ban",
    "number": "050",
    "tel": "880",
    "latitude": "24 00 n",
    "longitude": "90 00 e",
    "un": "bd"
  },
  "be": {
    "value": "be",
    "name": "belgium",
    "names": [
      "belgium",
      "belgien",
      "belgique",
      "bélgica"
    ],
    "region": "europe",
    "subregion": "western europe",
    "currency": "eur",
    "alpha2": "be",
    "alpha3": "bel",
    "ioc": "bel",
    "number": "056",
    "tel": "32",
    "latitude": "50 50 n",
    "longitude": "4 00 e",
    "un": "be"
  },
  "bf": {
    "value": "bf",
    "name": "burkina faso",
    "names": [
      "burkina faso"
    ],
    "region": "africa",
    "subregion": "western africa",
    "currency": "xof",
    "alpha2": "bf",
    "alpha3": "bfa",
    "ioc": "bur",
    "number": "854",
    "tel": "226",
    "latitude": "13 00 n",
    "longitude": "2 00 w",
    "un": "bf"
  },
  "bg": {
    "value": "bg",
    "name": "bulgaria",
    "names": [
      "bulgaria",
      "bulgarien",
      "bulgarie"
    ],
    "region": "europe",
    "subregion": "eastern europe",
    "currency": "bgn",
    "alpha2": "bg",
    "alpha3": "bgr",
    "ioc": "bul",
    "number": "100",
    "tel": "359",
    "latitude": "43 00 n",
    "longitude": "25 00 e",
    "un": "bg"
  },
  "bh": {
    "value": "bh",
    "name": "bahrain",
    "names": [
      "bahrain",
      "bahreïn",
      "bahrein"
    ],
    "region": "asia",
    "subregion": "western asia",
    "currency": "bhd",
    "alpha2": "bh",
    "alpha3": "bhr",
    "ioc": "brn",
    "number": "048",
    "tel": "973",
    "latitude": "26 00 n",
    "longitude": "50 33 e",
    "un": "bh"
  },
  "bi": {
    "value": "bi",
    "name": "burundi",
    "names": [
      "burundi"
    ],
    "region": "africa",
    "subregion": "eastern africa",
    "currency": "bif",
    "alpha2": "bi",
    "alpha3": "bdi",
    "ioc": "bdi",
    "number": "108",
    "tel": "257",
    "latitude": "3 30 s",
    "longitude": "30 00 e",
    "un": "bi"
  },
  "bj": {
    "value": "bj",
    "name": "benin",
    "names": [
      "benin",
      "bénin"
    ],
    "region": "africa",
    "subregion": "western africa",
    "currency": "xof",
    "alpha2": "bj",
    "alpha3": "ben",
    "ioc": "ben",
    "number": "204",
    "tel": "229",
    "latitude": "9 30 n",
    "longitude": "2 15 e",
    "un": "bj"
  },
  "bl": {
    "value": "bl",
    "name": "saint barthélemy",
    "names": [
      "saint barthélemy"
    ],
    "region": "americas",
    "subregion": "caribbean",
    "currency": null,
    "alpha2": "bl",
    "alpha3": "blm",
    "ioc": null,
    "number": "652",
    "tel": "590",
    "latitude": "17 90 n",
    "longitude": "62 85 w",
    "un": null
  },
  "bm": {
    "value": "bm",
    "name": "bermuda",
    "names": [
      "bermuda",
      "bermudes",
      "bermudas"
    ],
    "region": "americas",
    "subregion": "northern america",
    "currency": "bmd",
    "alpha2": "bm",
    "alpha3": "bmu",
    "ioc": "ber",
    "number": "060",
    "tel": "1",
    "latitude": "32 20 n",
    "longitude": "64 45 w",
    "un": "bm"
  },
  "bn": {
    "value": "bn",
    "name": "brunei darussalam",
    "names": [
      "brunei"
    ],
    "region": "asia",
    "subregion": "south-eastern asia",
    "currency": "bnd",
    "alpha2": "bn",
    "alpha3": "brn",
    "ioc": "bru",
    "number": "096",
    "tel": "673",
    "latitude": "4 30 n",
    "longitude": "114 40 e",
    "un": "bn"
  },
  "bo": {
    "value": "bo",
    "name": "bolivia",
    "names": [
      "bolivia",
      "bolivien",
      "bolivie"
    ],
    "region": "americas",
    "subregion": "south america",
    "currency": "bob",
    "alpha2": "bo",
    "alpha3": "bol",
    "ioc": "bol",
    "number": "068",
    "tel": "591",
    "latitude": "17 00 s",
    "longitude": "65 00 w",
    "un": "bo"
  },
  "br": {
    "value": "br",
    "name": "brazil",
    "names": [
      "brazil",
      "brasilien",
      "brésil",
      "brasil"
    ],
    "region": "americas",
    "subregion": "south america",
    "currency": "brl",
    "alpha2": "br",
    "alpha3": "bra",
    "ioc": "bra",
    "number": "076",
    "tel": "55",
    "latitude": "10 00 s",
    "longitude": "55 00 w",
    "un": "br"
  },
  "bs": {
    "value": "bs",
    "name": "bahamas",
    "names": [
      "bahamas"
    ],
    "region": "americas",
    "subregion": "caribbean",
    "currency": "bsd",
    "alpha2": "bs",
    "alpha3": "bhs",
    "ioc": "bah",
    "number": "044",
    "tel": "1",
    "latitude": "24 15 n",
    "longitude": "76 00 w",
    "un": "bs"
  },
  "bt": {
    "value": "bt",
    "name": "bhutan",
    "names": [
      "bhutan",
      "bhoutan",
      "bután"
    ],
    "region": "asia",
    "subregion": "southern asia",
    "currency": "btn",
    "alpha2": "bt",
    "alpha3": "btn",
    "ioc": "bhu",
    "number": "064",
    "tel": "975",
    "latitude": "27 30 n",
    "longitude": "90 30 e",
    "un": "bt"
  },
  "bv": {
    "value": "bv",
    "name": "bouvet island",
    "names": [
      "bouvet island"
    ],
    "region": "",
    "subregion": "",
    "currency": "nok",
    "alpha2": "bv",
    "alpha3": "bvt",
    "ioc": null,
    "number": "074",
    "tel": "",
    "latitude": "54 26 s",
    "longitude": "3 24 e",
    "un": null
  },
  "bw": {
    "value": "bw",
    "name": "botswana",
    "names": [
      "botswana"
    ],
    "region": "africa",
    "subregion": "southern africa",
    "currency": "bwp",
    "alpha2": "bw",
    "alpha3": "bwa",
    "ioc": "bot",
    "number": "072",
    "tel": "267",
    "latitude": "22 00 s",
    "longitude": "24 00 e",
    "un": "bw"
  },
  "by": {
    "value": "by",
    "name": "belarus",
    "names": [
      "belarus",
      "weißrussland",
      "biélorussie",
      "bielorrusia"
    ],
    "region": "europe",
    "subregion": "eastern europe",
    "currency": "byr",
    "alpha2": "by",
    "alpha3": "blr",
    "ioc": "blr",
    "number": "112",
    "tel": "375",
    "latitude": "53 00 n",
    "longitude": "28 00 e",
    "un": "by"
  },
  "bz": {
    "value": "bz",
    "name": "belize",
    "names": [
      "belize",
      "belice"
    ],
    "region": "americas",
    "subregion": "central america",
    "currency": "bzd",
    "alpha2": "bz",
    "alpha3": "blz",
    "ioc": "biz",
    "number": "084",
    "tel": "501",
    "latitude": "17 15 n",
    "longitude": "88 45 w",
    "un": "bz"
  },
  "ca": {
    "value": "ca",
    "name": "canada",
    "names": [
      "canada",
      "kanada",
      "canadá"
    ],
    "region": "americas",
    "subregion": "northern america",
    "currency": "cad",
    "alpha2": "ca",
    "alpha3": "can",
    "ioc": "can",
    "number": "124",
    "tel": "1",
    "latitude": "60 00 n",
    "longitude": "95 00 w",
    "un": "ca"
  },
  "cc": {
    "value": "cc",
    "name": "cocos (keeling) islands",
    "names": [
      "cocos (keeling) islands"
    ],
    "region": "oceania",
    "subregion": "australia and new zealand",
    "currency": "aud",
    "alpha2": "cc",
    "alpha3": "cck",
    "ioc": null,
    "number": "166",
    "tel": "61",
    "latitude": "12 30 s",
    "longitude": "96 50 e",
    "un": "cc"
  },
  "cd": {
    "value": "cd",
    "name": "congo, the democratic republic of the",
    "names": [
      "congo (dem. rep.)",
      "kongo (dem. rep.)",
      "congo (rep. dem.)",
      "congo (rep. dem.)"
    ],
    "region": "africa",
    "subregion": "middle africa",
    "currency": null,
    "alpha2": "cd",
    "alpha3": "cod",
    "ioc": "cod",
    "number": "180",
    "tel": "243",
    "latitude": "0 00 n",
    "longitude": "25 00 e",
    "un": "cd"
  },
  "cf": {
    "value": "cf",
    "name": "central african republic",
    "names": [
      "central african republic",
      "zentralafrikanische republik",
      "république centrafricaine",
      "república centroafricana"
    ],
    "region": "africa",
    "subregion": "middle africa",
    "currency": "xaf",
    "alpha2": "cf",
    "alpha3": "caf",
    "ioc": "caf",
    "number": "140",
    "tel": "236",
    "latitude": "7 00 n",
    "longitude": "21 00 e",
    "un": "cf"
  },
  "cg": {
    "value": "cg",
    "name": "congo",
    "names": [
      "congo",
      "kongo"
    ],
    "region": "africa",
    "subregion": "middle africa",
    "currency": null,
    "alpha2": "cg",
    "alpha3": "cog",
    "ioc": "cgo",
    "number": "178",
    "tel": "242",
    "latitude": "1 00 s",
    "longitude": "15 00 e",
    "un": "cg"
  },
  "ch": {
    "value": "ch",
    "name": "switzerland",
    "names": [
      "switzerland",
      "schweiz",
      "suisse",
      "suiza"
    ],
    "region": "europe",
    "subregion": "western europe",
    "currency": "chf",
    "alpha2": "ch",
    "alpha3": "che",
    "ioc": "sui",
    "number": "756",
    "tel": "41",
    "latitude": "47 00 n",
    "longitude": "8 00 e",
    "un": "ch"
  },
  "ci": {
    "value": "ci",
    "name": "côte d'ivoire",
    "names": [
      "côte d'ivoire"
    ],
    "region": "africa",
    "subregion": "western africa",
    "currency": "xof",
    "alpha2": "ci",
    "alpha3": "civ",
    "ioc": "civ",
    "number": "384",
    "tel": "225",
    "latitude": "8 00 n",
    "longitude": "5 00 w",
    "un": "ci"
  },
  "ck": {
    "value": "ck",
    "name": "cook islands",
    "names": [
      "cook islands",
      "cookinseln",
      "îles cook",
      "islas cook"
    ],
    "region": "oceania",
    "subregion": "polynesia",
    "currency": "nzd",
    "alpha2": "ck",
    "alpha3": "cok",
    "ioc": "cok",
    "number": "184",
    "tel": "682",
    "latitude": "21 14 s",
    "longitude": "159 46 w",
    "un": "ck"
  },
  "cl": {
    "value": "cl",
    "name": "chile",
    "names": [
      "chile"
    ],
    "region": "americas",
    "subregion": "south america",
    "currency": "clp",
    "alpha2": "cl",
    "alpha3": "chl",
    "ioc": "chi",
    "number": "152",
    "tel": "56",
    "latitude": "30 00 s",
    "longitude": "71 00 w",
    "un": "cl"
  },
  "cm": {
    "value": "cm",
    "name": "cameroon",
    "names": [
      "cameroon",
      "kamerun",
      "cameroun",
      "camerún"
    ],
    "region": "africa",
    "subregion": "middle africa",
    "currency": "xaf",
    "alpha2": "cm",
    "alpha3": "cmr",
    "ioc": "cmr",
    "number": "120",
    "tel": "237",
    "latitude": "6 00 n",
    "longitude": "12 00 e",
    "un": "cm"
  },
  "cn": {
    "value": "cn",
    "name": "china",
    "names": [
      "china",
      "chine"
    ],
    "region": "asia",
    "subregion": "eastern asia",
    "currency": "cny",
    "alpha2": "cn",
    "alpha3": "chn",
    "ioc": "chn",
    "number": "156",
    "tel": "86",
    "latitude": "35 00 n",
    "longitude": "105 00 e",
    "un": "cn"
  },
  "co": {
    "value": "co",
    "name": "colombia",
    "names": [
      "colombia",
      "kolumbien",
      "colombie"
    ],
    "region": "americas",
    "subregion": "south america",
    "currency": "cop",
    "alpha2": "co",
    "alpha3": "col",
    "ioc": "col",
    "number": "170",
    "tel": "57",
    "latitude": "4 00 n",
    "longitude": "72 00 w",
    "un": "co"
  },
  "cr": {
    "value": "cr",
    "name": "costa rica",
    "names": [
      "costa rica"
    ],
    "region": "americas",
    "subregion": "central america",
    "currency": "crc",
    "alpha2": "cr",
    "alpha3": "cri",
    "ioc": "crc",
    "number": "188",
    "tel": "506",
    "latitude": "10 00 n",
    "longitude": "84 00 w",
    "un": "cr"
  },
  "cu": {
    "value": "cu",
    "name": "cuba",
    "names": [
      "cuba",
      "kuba"
    ],
    "region": "americas",
    "subregion": "caribbean",
    "currency": "cup",
    "alpha2": "cu",
    "alpha3": "cub",
    "ioc": "cub",
    "number": "192",
    "tel": "53",
    "latitude": "21 30 n",
    "longitude": "80 00 w",
    "un": "cu"
  },
  "cv": {
    "value": "cv",
    "name": "cape verde",
    "names": [
      "cape verde",
      "kap verde",
      "cap vert",
      "cabo verde"
    ],
    "region": "africa",
    "subregion": "western africa",
    "currency": "cve",
    "alpha2": "cv",
    "alpha3": "cpv",
    "ioc": "cpv",
    "number": "132",
    "tel": "238",
    "latitude": "16 00 n",
    "longitude": "24 00 w",
    "un": "cv"
  },
  "cx": {
    "value": "cx",
    "name": "christmas island",
    "names": [
      "christmas island"
    ],
    "region": "oceania",
    "subregion": "australia and new zealand",
    "currency": "aud",
    "alpha2": "cx",
    "alpha3": "cxr",
    "ioc": null,
    "number": "162",
    "tel": "61",
    "latitude": "10 30 s",
    "longitude": "105 40 e",
    "un": "cx"
  },
  "cy": {
    "value": "cy",
    "name": "cyprus",
    "names": [
      "cyprus",
      "zypern",
      "chypre",
      "chipre"
    ],
    "region": "asia",
    "subregion": "western asia",
    "currency": "eur",
    "alpha2": "cy",
    "alpha3": "cyp",
    "ioc": "cyp",
    "number": "196",
    "tel": "357",
    "latitude": "35 00 n",
    "longitude": "33 00 e",
    "un": "cy"
  },
  "cz": {
    "value": "cz",
    "name": "czech republic",
    "names": [
      "czech republic",
      "tschechische republik",
      "république tchèque",
      "república checa"
    ],
    "region": "europe",
    "subregion": "eastern europe",
    "currency": "czk",
    "alpha2": "cz",
    "alpha3": "cze",
    "ioc": "cze",
    "number": "203",
    "tel": "420",
    "latitude": "49 45 n",
    "longitude": "15 30 e",
    "un": "cz"
  },
  "de": {
    "value": "de",
    "name": "germany",
    "names": [
      "germany",
      "deutschland",
      "allemagne",
      "alemania"
    ],
    "region": "europe",
    "subregion": "western europe",
    "currency": "eur",
    "alpha2": "de",
    "alpha3": "deu",
    "ioc": "ger",
    "number": "276",
    "tel": "49",
    "latitude": "51 00 n",
    "longitude": "9 00 e",
    "un": "de"
  },
  "dj": {
    "value": "dj",
    "name": "djibouti",
    "names": [
      "djibouti"
    ],
    "region": "africa",
    "subregion": "eastern africa",
    "currency": "djf",
    "alpha2": "dj",
    "alpha3": "dji",
    "ioc": "dji",
    "number": "262",
    "tel": "253",
    "latitude": "11 30 n",
    "longitude": "43 00 e",
    "un": "dj"
  },
  "dk": {
    "value": "dk",
    "name": "denmark",
    "names": [
      "denmark",
      "dänemark",
      "danemark",
      "dinamarca"
    ],
    "region": "europe",
    "subregion": "northern europe",
    "currency": "dkk",
    "alpha2": "dk",
    "alpha3": "dnk",
    "ioc": "den",
    "number": "208",
    "tel": "45",
    "latitude": "56 00 n",
    "longitude": "10 00 e",
    "un": "dk"
  },
  "dm": {
    "value": "dm",
    "name": "dominica",
    "names": [
      "dominica"
    ],
    "region": "americas",
    "subregion": "caribbean",
    "currency": "xcd",
    "alpha2": "dm",
    "alpha3": "dma",
    "ioc": "dma",
    "number": "212",
    "tel": "1",
    "latitude": "15 25 n",
    "longitude": "61 20 w",
    "un": "dm"
  },
  "do": {
    "value": "do",
    "name": "dominican republic",
    "names": [
      "dominican republic",
      "dominikanische republik",
      "république dominicaine",
      "república dominicana"
    ],
    "region": "americas",
    "subregion": "caribbean",
    "currency": "dop",
    "alpha2": "do",
    "alpha3": "dom",
    "ioc": "dom",
    "number": "214",
    "tel": "1",
    "latitude": "19 00 n",
    "longitude": "70 40 w",
    "un": "do"
  },
  "dz": {
    "value": "dz",
    "name": "algeria",
    "names": [
      "algeria",
      "algerien",
      "algérie",
      "argelia"
    ],
    "region": "africa",
    "subregion": "northern africa",
    "currency": "dzd",
    "alpha2": "dz",
    "alpha3": "dza",
    "ioc": "alg",
    "number": "012",
    "tel": "213",
    "latitude": "28 00 n",
    "longitude": "3 00 e",
    "un": "dz"
  },
  "ec": {
    "value": "ec",
    "name": "ecuador",
    "names": [
      "équateur",
      "ecuador"
    ],
    "region": "americas",
    "subregion": "south america",
    "currency": "usd",
    "alpha2": "ec",
    "alpha3": "ecu",
    "ioc": "ecu",
    "number": "218",
    "tel": "593",
    "latitude": "2 00 s",
    "longitude": "77 30 w",
    "un": "ec"
  },
  "ee": {
    "value": "ee",
    "name": "estonia",
    "names": [
      "estland",
      "estonie",
      "estonia"
    ],
    "region": "europe",
    "subregion": "northern europe",
    "currency": "eek",
    "alpha2": "ee",
    "alpha3": "est",
    "ioc": "est",
    "number": "233",
    "tel": "372",
    "latitude": "59 00 n",
    "longitude": "26 00 e",
    "un": "ee"
  },
  "eg": {
    "value": "eg",
    "name": "egypt",
    "names": [
      "egypt",
      "ägypten",
      "égypte",
      "egipto"
    ],
    "region": "africa",
    "subregion": "northern africa",
    "currency": "egp",
    "alpha2": "eg",
    "alpha3": "egy",
    "ioc": "egy",
    "number": "818",
    "tel": "20",
    "latitude": "27 00 n",
    "longitude": "30 00 e",
    "un": "eg"
  },
  "eh": {
    "value": "eh",
    "name": "western sahara",
    "names": [
      "western sahara",
      "westsahara",
      "sahara occidental",
      "sahara occidental"
    ],
    "region": "africa",
    "subregion": "northern africa",
    "currency": "mad",
    "alpha2": "eh",
    "alpha3": "esh",
    "ioc": null,
    "number": "732",
    "tel": "212",
    "latitude": "24 30 n",
    "longitude": "13 00 w",
    "un": "eh"
  },
  "er": {
    "value": "er",
    "name": "eritrea",
    "names": [
      "érythrée",
      "eritrea"
    ],
    "region": "africa",
    "subregion": "eastern africa",
    "currency": "etb",
    "alpha2": "er",
    "alpha3": "eri",
    "ioc": "eri",
    "number": "232",
    "tel": "291",
    "latitude": "15 00 n",
    "longitude": "39 00 e",
    "un": "er"
  },
  "es": {
    "value": "es",
    "name": "spain",
    "names": [
      "spain",
      "spanien",
      "espagne",
      "españa"
    ],
    "region": "europe",
    "subregion": "southern europe",
    "currency": "eur",
    "alpha2": "es",
    "alpha3": "esp",
    "ioc": "esp",
    "number": "724",
    "tel": "34",
    "latitude": "40 00 n",
    "longitude": "4 00 w",
    "un": "es"
  },
  "et": {
    "value": "et",
    "name": "ethiopia",
    "names": [
      "ethiopia",
      "äthiopien",
      "éthiopie",
      "etiopía"
    ],
    "region": "africa",
    "subregion": "eastern africa",
    "currency": "etb",
    "alpha2": "et",
    "alpha3": "eth",
    "ioc": "eth",
    "number": "231",
    "tel": "251",
    "latitude": "8 00 n",
    "longitude": "38 00 e",
    "un": "et"
  },
  "fi": {
    "value": "fi",
    "name": "finland",
    "names": [
      "finland",
      "finnland",
      "finlande",
      "finlandia"
    ],
    "region": "europe",
    "subregion": "northern europe",
    "currency": "eur",
    "alpha2": "fi",
    "alpha3": "fin",
    "ioc": null,
    "number": "246",
    "tel": "358",
    "latitude": "64 00 n",
    "longitude": "26 00 e",
    "un": null
  },
  "fj": {
    "value": "fj",
    "name": "fiji",
    "names": [
      "fiji",
      "fidschi",
      "fidji"
    ],
    "region": "oceania",
    "subregion": "melanesia",
    "currency": "usd",
    "alpha2": "fj",
    "alpha3": "fji",
    "ioc": "fij",
    "number": "242",
    "tel": "679",
    "latitude": "18 00 s",
    "longitude": "175 00 e",
    "un": "fj"
  },
  "fk": {
    "value": "fk",
    "name": "falkland islands (malvinas)",
    "names": [
      "falkland islands",
      "falklandinseln",
      "îles malouines",
      "islas malvinas"
    ],
    "region": "americas",
    "subregion": "south america",
    "currency": "fkp",
    "alpha2": "fk",
    "alpha3": "flk",
    "ioc": null,
    "number": "238",
    "tel": "500",
    "latitude": "51 45 s",
    "longitude": "59 00 w",
    "un": "fk"
  },
  "fm": {
    "value": "fm",
    "name": "micronesia, federated states of",
    "names": [
      "micronesia",
      "mikronesien",
      "micronésie",
      "micronesia"
    ],
    "region": "oceania",
    "subregion": "micronesia",
    "currency": "usd",
    "alpha2": "fm",
    "alpha3": "fsm",
    "ioc": "fsm",
    "number": "583",
    "tel": "691",
    "latitude": "6 55 n",
    "longitude": "158 15 e",
    "un": "fm"
  },
  "fo": {
    "value": "fo",
    "name": "faroe islands",
    "names": [
      "faroe islands",
      "färöer-inseln",
      "îles féroé",
      "islas faroe"
    ],
    "region": "europe",
    "subregion": "northern europe",
    "currency": "dkk",
    "alpha2": "fo",
    "alpha3": "fro",
    "ioc": "fro",
    "number": "234",
    "tel": "298",
    "latitude": "62 00 n",
    "longitude": "7 00 w",
    "un": "fo"
  },
  "fr": {
    "value": "fr",
    "name": "france",
    "names": [
      "france",
      "frankreich",
      "francia",
      "the french republic"
    ],
    "region": "europe",
    "subregion": "western europe",
    "currency": "eur",
    "alpha2": "fr",
    "alpha3": "fra",
    "ioc": "fra",
    "number": "250",
    "tel": "33",
    "latitude": "46 00 n",
    "longitude": "2 00 e ",
    "un": "fr"
  },
  "ga": {
    "value": "ga",
    "name": "gabon",
    "names": [
      "gabon",
      "gabun",
      "gabón"
    ],
    "region": "africa",
    "subregion": "middle africa",
    "currency": "xaf",
    "alpha2": "ga",
    "alpha3": "gab",
    "ioc": "gab",
    "number": "266",
    "tel": "241",
    "latitude": "1 00 s",
    "longitude": "11 45 e",
    "un": "ga"
  },
  "gb": {
    "value": "gb",
    "name": "united kingdom",
    "names": [
      "united kingdom",
      "groãâbritannien",
      "royaume-uni",
      "reino unido"
    ],
    "region": "europe",
    "subregion": "northern europe",
    "currency": "gbp",
    "alpha2": "gb",
    "alpha3": "gbr",
    "ioc": null,
    "number": "826",
    "tel": "44",
    "latitude": "54 00 n",
    "longitude": "2 00 w",
    "un": null
  },
  "gd": {
    "value": "gd",
    "name": "grenada",
    "names": [
      "grenada"
    ],
    "region": "americas",
    "subregion": "caribbean",
    "currency": "xcd",
    "alpha2": "gd",
    "alpha3": "grd",
    "ioc": "grn",
    "number": "308",
    "tel": "1",
    "latitude": "12 07 n",
    "longitude": "61 40 w",
    "un": "gd"
  },
  "ge": {
    "value": "ge",
    "name": "georgia",
    "names": [
      "georgien",
      "géorgie",
      "georgia"
    ],
    "region": "asia",
    "subregion": "western asia",
    "currency": "gel",
    "alpha2": "ge",
    "alpha3": "geo",
    "ioc": "geo",
    "number": "268",
    "tel": "995",
    "latitude": "42 00 n",
    "longitude": "43 30 e",
    "un": "ge"
  },
  "gf": {
    "value": "gf",
    "name": "french guiana",
    "names": [
      "french guiana",
      "französisch guyana",
      "guyane française",
      "guayana francesa"
    ],
    "region": "americas",
    "subregion": "south america",
    "currency": "eur",
    "alpha2": "gf",
    "alpha3": "guf",
    "ioc": null,
    "number": "254",
    "tel": "594",
    "latitude": "4 00 n",
    "longitude": "53 00 w ",
    "un": "gf"
  },
  "gg": {
    "value": "gg",
    "name": "guernsey",
    "names": [
      "guernsey and alderney",
      "guernsey und alderney",
      "guernsey et alderney",
      "guernsey y alderney"
    ],
    "region": "europe",
    "subregion": "northern europe",
    "currency": "ggp",
    "alpha2": "gg",
    "alpha3": "ggy",
    "ioc": null,
    "number": "831",
    "tel": "44",
    "latitude": "49 28 n",
    "longitude": "2 35 w",
    "un": null
  },
  "gh": {
    "value": "gh",
    "name": "ghana",
    "names": [
      "ghana"
    ],
    "region": "africa",
    "subregion": "western africa",
    "currency": "ghs",
    "alpha2": "gh",
    "alpha3": "gha",
    "ioc": "gha",
    "number": "288",
    "tel": "233",
    "latitude": "8 00 n",
    "longitude": "2 00 w",
    "un": "gh"
  },
  "gi": {
    "value": "gi",
    "name": "gibraltar",
    "names": [
      "gibraltar"
    ],
    "region": "europe",
    "subregion": "southern europe",
    "currency": "gip",
    "alpha2": "gi",
    "alpha3": "gib",
    "ioc": null,
    "number": "292",
    "tel": "350",
    "latitude": "36 08 n",
    "longitude": "5 21 w",
    "un": "gi"
  },
  "gl": {
    "value": "gl",
    "name": "greenland",
    "names": [
      "greenland",
      "grönland",
      "groenland",
      "groenlandia"
    ],
    "region": "americas",
    "subregion": "northern america",
    "currency": "dkk",
    "alpha2": "gl",
    "alpha3": "grl",
    "ioc": null,
    "number": "304",
    "tel": "299",
    "latitude": "72 00 n",
    "longitude": "40 00 w",
    "un": "gl"
  },
  "gm": {
    "value": "gm",
    "name": "gambia",
    "names": [
      "gambia"
    ],
    "region": "africa",
    "subregion": "western africa",
    "currency": "gmd",
    "alpha2": "gm",
    "alpha3": "gmb",
    "ioc": "gam",
    "number": "270",
    "tel": "220",
    "latitude": "13 28 n",
    "longitude": "16 34 w",
    "un": "gm"
  },
  "gn": {
    "value": "gn",
    "name": "guinea",
    "names": [
      "guinea",
      "guinea",
      "guinée",
      "guinea"
    ],
    "region": "africa",
    "subregion": "western africa",
    "currency": "gnf",
    "alpha2": "gn",
    "alpha3": "gin",
    "ioc": "gui",
    "number": "324",
    "tel": "224",
    "latitude": "11 00 n",
    "longitude": "10 00 w",
    "un": "gn"
  },
  "gp": {
    "value": "gp",
    "name": "guadeloupe",
    "names": [
      "guadeloupe",
      "guadalupe"
    ],
    "region": "americas",
    "subregion": "caribbean",
    "currency": "eur",
    "alpha2": "gp",
    "alpha3": "glp",
    "ioc": null,
    "number": "312",
    "tel": "590",
    "latitude": "",
    "longitude": "",
    "un": "gp"
  },
  "gq": {
    "value": "gq",
    "name": "equatorial guinea",
    "names": [
      "equatorial guinea",
      "äquatorial-guinea",
      "guinée équatoriale",
      "guinea ecuatorial"
    ],
    "region": "africa",
    "subregion": "middle africa",
    "currency": null,
    "alpha2": "gq",
    "alpha3": "gnq",
    "ioc": "geq",
    "number": "226",
    "tel": "240",
    "latitude": "2 00 n",
    "longitude": "10 00 e",
    "un": "gq"
  },
  "gr": {
    "value": "gr",
    "name": "greece",
    "names": [
      "greece",
      "griechenland",
      "grèce",
      "grecia"
    ],
    "region": "europe",
    "subregion": "southern europe",
    "currency": "eur",
    "alpha2": "gr",
    "alpha3": "grc",
    "ioc": "gre",
    "number": "300",
    "tel": "30",
    "latitude": "39 00 n",
    "longitude": "22 00 e",
    "un": "gr"
  },
  "gs": {
    "value": "gs",
    "name": "south georgia and the south sandwich islands",
    "names": [
      "south georgia and the south sandwich islands"
    ],
    "region": "americas",
    "subregion": "south america",
    "currency": null,
    "alpha2": "gs",
    "alpha3": "sgs",
    "ioc": null,
    "number": "239",
    "tel": "500",
    "latitude": "54 30 s",
    "longitude": "37 00 w",
    "un": "gs"
  },
  "gt": {
    "value": "gt",
    "name": "guatemala",
    "names": [
      "guatemala"
    ],
    "region": "americas",
    "subregion": "central america",
    "currency": "gtq",
    "alpha2": "gt",
    "alpha3": "gtm",
    "ioc": "gua",
    "number": "320",
    "tel": "502",
    "latitude": "15 30 n",
    "longitude": "90 15 w",
    "un": "gt"
  },
  "gu": {
    "value": "gu",
    "name": "guam",
    "names": [
      "guam"
    ],
    "region": "oceania",
    "subregion": "micronesia",
    "currency": "usd",
    "alpha2": "gu",
    "alpha3": "gum",
    "ioc": "gum",
    "number": "316",
    "tel": "1",
    "latitude": "13 28 n",
    "longitude": "144 47 e",
    "un": "gu"
  },
  "gw": {
    "value": "gw",
    "name": "guinea-bissau",
    "names": [
      "guinea-bissau",
      "guinée-bissau"
    ],
    "region": "africa",
    "subregion": "western africa",
    "currency": "xof",
    "alpha2": "gw",
    "alpha3": "gnb",
    "ioc": "gbs",
    "number": "624",
    "tel": "245",
    "latitude": "12 00 n",
    "longitude": "15 00 w",
    "un": "gw"
  },
  "gy": {
    "value": "gy",
    "name": "guyana",
    "names": [
      "guyana"
    ],
    "region": "americas",
    "subregion": "south america",
    "currency": "gyd",
    "alpha2": "gy",
    "alpha3": "guy",
    "ioc": "guy",
    "number": "328",
    "tel": "592",
    "latitude": "5 00 n",
    "longitude": "59 00 w",
    "un": "gy"
  },
  "hk": {
    "value": "hk",
    "name": "hong kong",
    "names": [
      "hong kong"
    ],
    "region": "asia",
    "subregion": "eastern asia",
    "currency": "hkd",
    "alpha2": "hk",
    "alpha3": "hkg",
    "ioc": "hkg",
    "number": "344",
    "tel": "852",
    "latitude": "22 15 n",
    "longitude": "114 10 e",
    "un": "hk"
  },
  "hm": {
    "value": "hm",
    "name": "heard and mcdonald islands",
    "names": [
      "heard and mcdonald islands"
    ],
    "region": "",
    "subregion": "",
    "currency": "aud",
    "alpha2": "hm",
    "alpha3": "hmd",
    "ioc": null,
    "number": "334",
    "tel": "",
    "latitude": "53 06 s",
    "longitude": "72 31 e",
    "un": "hm"
  },
  "hn": {
    "value": "hn",
    "name": "honduras",
    "names": [
      "honduras"
    ],
    "region": "americas",
    "subregion": "central america",
    "currency": "hnl",
    "alpha2": "hn",
    "alpha3": "hnd",
    "ioc": "hon",
    "number": "340",
    "tel": "504",
    "latitude": "15 00 n",
    "longitude": "86 30 w",
    "un": "hn"
  },
  "hr": {
    "value": "hr",
    "name": "croatia",
    "names": [
      "croatia",
      "kroatien",
      "croatie",
      "croacia"
    ],
    "region": "europe",
    "subregion": "southern europe",
    "currency": "hrk",
    "alpha2": "hr",
    "alpha3": "hrv",
    "ioc": "cro",
    "number": "191",
    "tel": "385",
    "latitude": "45 10 n",
    "longitude": "15 30 e",
    "un": "hr"
  },
  "ht": {
    "value": "ht",
    "name": "haiti",
    "names": [
      "haiti"
    ],
    "region": "americas",
    "subregion": "caribbean",
    "currency": "usd",
    "alpha2": "ht",
    "alpha3": "hti",
    "ioc": "hai",
    "number": "332",
    "tel": "509",
    "latitude": "19 00 n",
    "longitude": "72 25 w",
    "un": "ht"
  },
  "hu": {
    "value": "hu",
    "name": "hungary",
    "names": [
      "hungary",
      "ungarn",
      "hongrie",
      "hungría"
    ],
    "region": "europe",
    "subregion": "eastern europe",
    "currency": "huf",
    "alpha2": "hu",
    "alpha3": "hun",
    "ioc": "hun",
    "number": "348",
    "tel": "36",
    "latitude": "47 00 n",
    "longitude": "20 00 e",
    "un": "hu"
  },
  "id": {
    "value": "id",
    "name": "indonesia",
    "names": [
      "indonesia",
      "indonesien",
      "indonésie"
    ],
    "region": "asia",
    "subregion": "south-eastern asia",
    "currency": "idr",
    "alpha2": "id",
    "alpha3": "idn",
    "ioc": "ina",
    "number": "360",
    "tel": "62",
    "latitude": "5 00 s",
    "longitude": "120 00 e",
    "un": "id"
  },
  "ie": {
    "value": "ie",
    "name": "ireland",
    "names": [
      "ireland",
      "irland",
      "irlande",
      "irlanda"
    ],
    "region": "europe",
    "subregion": "northern europe",
    "currency": "eur",
    "alpha2": "ie",
    "alpha3": "irl",
    "ioc": "irl",
    "number": "372",
    "tel": "353",
    "latitude": "53 00 n",
    "longitude": "8 00 w",
    "un": "ie"
  },
  "il": {
    "value": "il",
    "name": "israel",
    "names": [
      "israël",
      "israel"
    ],
    "region": "asia",
    "subregion": "western asia",
    "currency": "ils",
    "alpha2": "il",
    "alpha3": "isr",
    "ioc": "isr",
    "number": "376",
    "tel": "972",
    "latitude": "31 30 n",
    "longitude": "34 45 e",
    "un": "il"
  },
  "im": {
    "value": "im",
    "name": "isle of man",
    "names": [
      "isle of man",
      "man",
      "île de man",
      "isla de man"
    ],
    "region": "europe",
    "subregion": "northern europe",
    "currency": "imp",
    "alpha2": "im",
    "alpha3": "imn",
    "ioc": null,
    "number": "833",
    "tel": "44",
    "latitude": "54 15 n",
    "longitude": "4 30 w",
    "un": null
  },
  "in": {
    "value": "in",
    "name": "india",
    "names": [
      "india",
      "indien",
      "inde"
    ],
    "region": "asia",
    "subregion": "southern asia",
    "currency": "inr",
    "alpha2": "in",
    "alpha3": "ind",
    "ioc": "ind",
    "number": "356",
    "tel": "91",
    "latitude": "20 00 n",
    "longitude": "77 00 e",
    "un": "in"
  },
  "io": {
    "value": "io",
    "name": "british indian ocean territory",
    "names": [
      "british indian ocean territory"
    ],
    "region": "africa",
    "subregion": "eastern africa",
    "currency": "usd",
    "alpha2": "io",
    "alpha3": "iot",
    "ioc": null,
    "number": "086",
    "tel": "246",
    "latitude": "6 00 s",
    "longitude": "71 30 e",
    "un": "io"
  },
  "iq": {
    "value": "iq",
    "name": "iraq",
    "names": [
      "iraq",
      "irak"
    ],
    "region": "asia",
    "subregion": "western asia",
    "currency": "iqd",
    "alpha2": "iq",
    "alpha3": "irq",
    "ioc": "irq",
    "number": "368",
    "tel": "964",
    "latitude": "33 00 n",
    "longitude": "44 00 e",
    "un": "iq"
  },
  "ir": {
    "value": "ir",
    "name": "iran, islamic republic of",
    "names": [
      "iran",
      "irán"
    ],
    "region": "asia",
    "subregion": "southern asia",
    "currency": "irr",
    "alpha2": "ir",
    "alpha3": "irn",
    "ioc": "iri",
    "number": "364",
    "tel": "98",
    "latitude": "32 00 n",
    "longitude": "53 00 e",
    "un": "ir"
  },
  "is": {
    "value": "is",
    "name": "iceland",
    "names": [
      "iceland",
      "island",
      "islande",
      "islandia"
    ],
    "region": "europe",
    "subregion": "northern europe",
    "currency": "isk",
    "alpha2": "is",
    "alpha3": "isl",
    "ioc": "isl",
    "number": "352",
    "tel": "354",
    "latitude": "65 00 n",
    "longitude": "18 00 w",
    "un": "is"
  },
  "it": {
    "value": "it",
    "name": "italy",
    "names": [
      "italy",
      "italien",
      "italie",
      "italia"
    ],
    "region": "europe",
    "subregion": "southern europe",
    "currency": "eur",
    "alpha2": "it",
    "alpha3": "ita",
    "ioc": "ita",
    "number": "380",
    "tel": "39",
    "latitude": "42 50 n",
    "longitude": "12 50 e",
    "un": "it"
  },
  "je": {
    "value": "je",
    "name": "jersey",
    "names": [
      "jersey"
    ],
    "region": "europe",
    "subregion": "northern europe",
    "currency": "jep",
    "alpha2": "je",
    "alpha3": "jey",
    "ioc": null,
    "number": "832",
    "tel": "44",
    "latitude": "49 15 n",
    "longitude": "2 10 w",
    "un": null
  },
  "jm": {
    "value": "jm",
    "name": "jamaica",
    "names": [
      "jamaica",
      "jamaika",
      "jamaïque"
    ],
    "region": "americas",
    "subregion": "caribbean",
    "currency": "jmd",
    "alpha2": "jm",
    "alpha3": "jam",
    "ioc": "jam",
    "number": "388",
    "tel": "1",
    "latitude": "18 15 n",
    "longitude": "77 30 w",
    "un": "jm"
  },
  "jo": {
    "value": "jo",
    "name": "jordan",
    "names": [
      "jordan",
      "jordanien",
      "jordanie",
      "jordania"
    ],
    "region": "asia",
    "subregion": "western asia",
    "currency": "jod",
    "alpha2": "jo",
    "alpha3": "jor",
    "ioc": "jor",
    "number": "400",
    "tel": "962",
    "latitude": "31 00 n",
    "longitude": "36 00 e",
    "un": "jo"
  },
  "jp": {
    "value": "jp",
    "name": "japan",
    "names": [
      "japan",
      "japan",
      "japon",
      "japón"
    ],
    "region": "asia",
    "subregion": "eastern asia",
    "currency": "jpy",
    "alpha2": "jp",
    "alpha3": "jpn",
    "ioc": "jpn",
    "number": "392",
    "tel": "81",
    "latitude": "36 00 n",
    "longitude": "138 00 e",
    "un": "jp"
  },
  "ke": {
    "value": "ke",
    "name": "kenya",
    "names": [
      "kenya",
      "kenia",
      "kenya",
      "kenia"
    ],
    "region": "africa",
    "subregion": "eastern africa",
    "currency": "kes",
    "alpha2": "ke",
    "alpha3": "ken",
    "ioc": "ken",
    "number": "404",
    "tel": "254",
    "latitude": "1 00 n",
    "longitude": "38 00 e",
    "un": "ke"
  },
  "kg": {
    "value": "kg",
    "name": "kyrgyzstan",
    "names": [
      "kyrgyzstan",
      "kirgisistan",
      "kirghizistan",
      "kirguizistán"
    ],
    "region": "asia",
    "subregion": "central asia",
    "currency": "kgs",
    "alpha2": "kg",
    "alpha3": "kgz",
    "ioc": "kgz",
    "number": "417",
    "tel": "996",
    "latitude": "41 00 n",
    "longitude": "75 00 e",
    "un": "kg"
  },
  "kh": {
    "value": "kh",
    "name": "cambodia",
    "names": [
      "cambodia",
      "kambodscha",
      "cambodge",
      "camboya"
    ],
    "region": "asia",
    "subregion": "south-eastern asia",
    "currency": "khr",
    "alpha2": "kh",
    "alpha3": "khm",
    "ioc": "cam",
    "number": "116",
    "tel": "855",
    "latitude": "13 00 n",
    "longitude": "105 00 e",
    "un": "kh"
  },
  "ki": {
    "value": "ki",
    "name": "kiribati",
    "names": [
      "kiribati",
      "kiribati",
      "kiribati",
      "kiribati"
    ],
    "region": "oceania",
    "subregion": "micronesia",
    "currency": "aud",
    "alpha2": "ki",
    "alpha3": "kir",
    "ioc": "kir",
    "number": "296",
    "tel": "686",
    "latitude": "1 25 n",
    "longitude": "173 00 e",
    "un": "ki"
  },
  "km": {
    "value": "km",
    "name": "comoros",
    "names": [
      "comoros",
      "komoren",
      "comores"
    ],
    "region": "africa",
    "subregion": "eastern africa",
    "currency": "kmf",
    "alpha2": "km",
    "alpha3": "com",
    "ioc": "com",
    "number": "174",
    "tel": "269",
    "latitude": "12 10 s",
    "longitude": "44 15 e",
    "un": "km"
  },
  "kn": {
    "value": "kn",
    "name": "saint kitts and nevis",
    "names": [
      "saint kitts and nevis",
      "saint kitts et nevis",
      "saint kitts y nevis"
    ],
    "region": "americas",
    "subregion": "caribbean",
    "currency": "xcd",
    "alpha2": "kn",
    "alpha3": "kna",
    "ioc": "skn",
    "number": "659",
    "tel": "1",
    "latitude": "17 20 n",
    "longitude": "62 45 w",
    "un": "kn"
  },
  "kp": {
    "value": "kp",
    "name": "korea, democratic people's republic of",
    "names": [
      "korea (north)",
      "nordkorea",
      "corée du nord",
      "corea del norte"
    ],
    "region": "asia",
    "subregion": "eastern asia",
    "currency": "kpw",
    "alpha2": "kp",
    "alpha3": "prk",
    "ioc": "prk",
    "number": "408",
    "tel": "850",
    "latitude": "40 00 n",
    "longitude": "127 00 e",
    "un": "kp"
  },
  "kr": {
    "value": "kr",
    "name": "korea, republic of",
    "names": [
	  "south korea",
      "korea (south)",
      "südkorea",
      "corée du sud",
      "corea del sur"
    ],
    "region": "asia",
    "subregion": "eastern asia",
    "currency": "krw",
    "alpha2": "kr",
    "alpha3": "kor",
    "ioc": "kor",
    "number": "410",
    "tel": "82",
    "latitude": "37 00 n",
    "longitude": "127 30 e",
    "un": "kr"
  },
  "kw": {
    "value": "kw",
    "name": "kuwait",
    "names": [
      "koweït",
      "kuwait"
    ],
    "region": "asia",
    "subregion": "western asia",
    "currency": "kwd",
    "alpha2": "kw",
    "alpha3": "kwt",
    "ioc": "kuw",
    "number": "414",
    "tel": "965",
    "latitude": "29 30 n",
    "longitude": "45 45 e",
    "un": "kw"
  },
  "ky": {
    "value": "ky",
    "name": "cayman islands",
    "names": [
      "cayman islands",
      "cayman-inseln",
      "îles caïmans",
      "islas caimán"
    ],
    "region": "americas",
    "subregion": "caribbean",
    "currency": "kyd",
    "alpha2": "ky",
    "alpha3": "cym",
    "ioc": "cay",
    "number": "136",
    "tel": "1",
    "latitude": "19 30 n",
    "longitude": "80 30 w",
    "un": "ky"
  },
  "kz": {
    "value": "kz",
    "name": "kazakhstan",
    "names": [
      "kazakhstan",
      "kasachstan",
      "kazakhstan",
      "kazajistán"
    ],
    "region": "asia",
    "subregion": "central asia",
    "currency": "kzt",
    "alpha2": "kz",
    "alpha3": "kaz",
    "ioc": "kaz",
    "number": "398",
    "tel": "7",
    "latitude": "48 00 n",
    "longitude": "68 00 e",
    "un": "kz"
  },
  "la": {
    "value": "la",
    "name": "lao people's democratic republic",
    "names": [
      "laos",
      "laos",
      "laos",
      "laos"
    ],
    "region": "asia",
    "subregion": "south-eastern asia",
    "currency": "lak",
    "alpha2": "la",
    "alpha3": "lao",
    "ioc": "lao",
    "number": "418",
    "tel": "856",
    "latitude": "18 00 n",
    "longitude": "105 00 e",
    "un": "la",
    "commonname": "laos"
  },
  "lb": {
    "value": "lb",
    "name": "lebanon",
    "names": [
      "lebanon",
      "libanon",
      "liban",
      "líbano"
    ],
    "region": "asia",
    "subregion": "western asia",
    "currency": "lbp",
    "alpha2": "lb",
    "alpha3": "lbn",
    "ioc": "lib",
    "number": "422",
    "tel": "961",
    "latitude": "33 50 n",
    "longitude": "35 50 e",
    "un": "lb"
  },
  "lc": {
    "value": "lc",
    "name": "saint lucia",
    "names": [
      "saint lucia",
      "saint-lucie",
      "santa lucía"
    ],
    "region": "americas",
    "subregion": "caribbean",
    "currency": "xcd",
    "alpha2": "lc",
    "alpha3": "lca",
    "ioc": "lca",
    "number": "662",
    "tel": "1",
    "latitude": "13 53 n",
    "longitude": "60 58 w",
    "un": "lc"
  },
  "li": {
    "value": "li",
    "name": "liechtenstein",
    "names": [
      "liechtenstein"
    ],
    "region": "europe",
    "subregion": "western europe",
    "currency": "chf",
    "alpha2": "li",
    "alpha3": "lie",
    "ioc": "lie",
    "number": "438",
    "tel": "423",
    "latitude": "47 16 n",
    "longitude": "9 32 e",
    "un": "li"
  },
  "lk": {
    "value": "lk",
    "name": "sri lanka",
    "names": [
      "sri lanka"
    ],
    "region": "asia",
    "subregion": "southern asia",
    "currency": "lkr",
    "alpha2": "lk",
    "alpha3": "lka",
    "ioc": "sri",
    "number": "144",
    "tel": "94",
    "latitude": "7 00 n",
    "longitude": "81 00 e",
    "un": "lk"
  },
  "lr": {
    "value": "lr",
    "name": "liberia",
    "names": [
      "liberia",
      "liberia",
      "liberia",
      "liberia"
    ],
    "region": "africa",
    "subregion": "western africa",
    "currency": "lrd",
    "alpha2": "lr",
    "alpha3": "lbr",
    "ioc": "lbr",
    "number": "430",
    "tel": "231",
    "latitude": "6 30 n",
    "longitude": "9 30 w",
    "un": "lr"
  },
  "ls": {
    "value": "ls",
    "name": "lesotho",
    "names": [
      "lesotho",
      "lesotho",
      "lesotho",
      "lesotho"
    ],
    "region": "africa",
    "subregion": "southern africa",
    "currency": "lsl",
    "alpha2": "ls",
    "alpha3": "lso",
    "ioc": "les",
    "number": "426",
    "tel": "266",
    "latitude": "29 30 s",
    "longitude": "28 30 e",
    "un": "ls"
  },
  "lt": {
    "value": "lt",
    "name": "lithuania",
    "names": [
      "lithuania",
      "litauen",
      "lituanie",
      "lituania"
    ],
    "region": "europe",
    "subregion": "northern europe",
    "currency": "ltl",
    "alpha2": "lt",
    "alpha3": "ltu",
    "ioc": "ltu",
    "number": "440",
    "tel": "370",
    "latitude": "56 00 n",
    "longitude": "24 00 e",
    "un": "lt"
  },
  "lu": {
    "value": "lu",
    "name": "luxembourg",
    "names": [
      "luxembourg",
      "luxemburg",
      "luxembourg",
      "luxemburgo"
    ],
    "region": "europe",
    "subregion": "western europe",
    "currency": "eur",
    "alpha2": "lu",
    "alpha3": "lux",
    "ioc": "lux",
    "number": "442",
    "tel": "352",
    "latitude": "49 45 n",
    "longitude": "6 10 e",
    "un": "lu"
  },
  "lv": {
    "value": "lv",
    "name": "latvia",
    "names": [
      "latvia",
      "lettland",
      "lettonie",
      "letonia"
    ],
    "region": "europe",
    "subregion": "northern europe",
    "currency": "lvl",
    "alpha2": "lv",
    "alpha3": "lva",
    "ioc": "lat",
    "number": "428",
    "tel": "371",
    "latitude": "57 00 n",
    "longitude": "25 00 e",
    "un": "lv"
  },
  "ly": {
    "value": "ly",
    "name": "libyan arab jamahiriya",
    "names": [
      "libya",
      "libyen",
      "libye",
      "libia"
    ],
    "region": "africa",
    "subregion": "northern africa",
    "currency": "lyd",
    "alpha2": "ly",
    "alpha3": "lby",
    "ioc": "lba",
    "number": "434",
    "tel": "218",
    "latitude": "25 00 n",
    "longitude": "17 00 e",
    "un": "ly"
  },
  "ma": {
    "value": "ma",
    "name": "morocco",
    "names": [
      "morocco",
      "marokko",
      "maroc",
      "marruecos"
    ],
    "region": "africa",
    "subregion": "northern africa",
    "currency": "mad",
    "alpha2": "ma",
    "alpha3": "mar",
    "ioc": "mar",
    "number": "504",
    "tel": "212",
    "latitude": "32 00 n",
    "longitude": "5 00 w",
    "un": "ma"
  },
  "mc": {
    "value": "mc",
    "name": "monaco",
    "names": [
      "monaco",
      "mónaco"
    ],
    "region": "europe",
    "subregion": "western europe",
    "currency": "eur",
    "alpha2": "mc",
    "alpha3": "mco",
    "ioc": "mon",
    "number": "492",
    "tel": "377",
    "latitude": "43 44 n",
    "longitude": "7 24 e",
    "un": "mc"
  },
  "md": {
    "value": "md",
    "name": "moldova, republic of",
    "names": [
      "moldova",
      "moldawien",
      "moldavie",
      "moldavia",
      "the republic of moldova"
    ],
    "region": "europe",
    "subregion": "eastern europe",
    "currency": "mdl",
    "alpha2": "md",
    "alpha3": "mda",
    "ioc": "mda",
    "number": "498",
    "tel": "373",
    "latitude": "47 00 n",
    "longitude": "29 00 e",
    "un": "md"
  },
  "me": {
    "value": "me",
    "name": "montenegro",
    "names": [
      "crna gora",
      "montenegro"
    ],
    "region": "europe",
    "subregion": "southern europe",
    "currency": "eur",
    "alpha2": "me",
    "alpha3": "mne",
    "ioc": "mne",
    "number": "499",
    "tel": "382",
    "latitude": "42 30 n",
    "longitude": "19 18 e",
    "un": "me"
  },
  "mf": {
    "value": "mf",
    "name": "saint martin",
    "names": [
      "saint martin"
    ],
    "region": "americas",
    "subregion": "caribbean",
    "currency": "eur",
    "alpha2": "mf",
    "alpha3": "maf",
    "ioc": null,
    "number": "663",
    "tel": "590",
    "latitude": "18 05 n",
    "longitude": "63 57 w",
    "un": null
  },
  "mg": {
    "value": "mg",
    "name": "madagascar",
    "names": [
      "madagascar",
      "madagaskar",
      "the republic of madagascar"
    ],
    "region": "africa",
    "subregion": "eastern africa",
    "currency": null,
    "alpha2": "mg",
    "alpha3": "mdg",
    "ioc": "mad",
    "number": "450",
    "tel": "261",
    "latitude": "20 00 s",
    "longitude": "47 00 e",
    "un": "mg"
  },
  "mh": {
    "value": "mh",
    "name": "marshall islands",
    "names": [
      "marshall islands",
      "marshall-inseln",
      "îles marshall",
      "islas marshall"
    ],
    "region": "oceania",
    "subregion": "micronesia",
    "currency": "usd",
    "alpha2": "mh",
    "alpha3": "mhl",
    "ioc": "mhl",
    "number": "584",
    "tel": "692",
    "latitude": "9 00 n",
    "longitude": "168 00 e",
    "un": "mh"
  },
  "mk": {
    "value": "mk",
    "name": "macedonia, the former yugoslav republic of",
    "names": [
      "macedonia",
      "mazedonien",
      "macédoine",
      "macedonia"
    ],
    "region": "europe",
    "subregion": "southern europe",
    "currency": null,
    "alpha2": "mk",
    "alpha3": "mkd",
    "ioc": "mkd",
    "number": "807",
    "tel": "389",
    "latitude": "41 50 n",
    "longitude": "22 00 e",
    "un": "mk"
  },
  "ml": {
    "value": "ml",
    "name": "mali",
    "names": [
      "mali"
    ],
    "region": "africa",
    "subregion": "western africa",
    "currency": "xof",
    "alpha2": "ml",
    "alpha3": "mli",
    "ioc": "mli",
    "number": "466",
    "tel": "223",
    "latitude": "17 00 n",
    "longitude": "4 00 w",
    "un": "ml"
  },
  "mm": {
    "value": "mm",
    "name": "myanmar",
    "names": [
      "myanmar",
      "myanmar",
      "myanmar",
      "myanmar"
    ],
    "region": "asia",
    "subregion": "south-eastern asia",
    "currency": "mnk",
    "alpha2": "mm",
    "alpha3": "mmr",
    "ioc": "mya",
    "number": "104",
    "tel": "95",
    "latitude": "22 00 n",
    "longitude": "98 00 e",
    "un": "mm"
  },
  "mn": {
    "value": "mn",
    "name": "mongolia",
    "names": [
      "mongolei",
      "mongolie",
      "mongolia"
    ],
    "region": "asia",
    "subregion": "eastern asia",
    "currency": "mnt",
    "alpha2": "mn",
    "alpha3": "mng",
    "ioc": "mgl",
    "number": "496",
    "tel": "976",
    "latitude": "46 00 n",
    "longitude": "105 00 e",
    "un": "mn"
  },
  "mo": {
    "value": "mo",
    "name": "macao",
    "names": [
      "macao"
    ],
    "region": "asia",
    "subregion": "eastern asia",
    "currency": "mop",
    "alpha2": "mo",
    "alpha3": "mac",
    "ioc": null,
    "number": "446",
    "tel": "853",
    "latitude": "22 10 n",
    "longitude": "113 33 e",
    "un": "mo"
  },
  "mp": {
    "value": "mp",
    "name": "northern mariana islands",
    "names": [
      "northern mariana islands",
      "nördliche marianen",
      "mariannes du nord",
      "islas marianas del norte"
    ],
    "region": "oceania",
    "subregion": "micronesia",
    "currency": "usd",
    "alpha2": "mp",
    "alpha3": "mnp",
    "ioc": null,
    "number": "580",
    "tel": "1",
    "latitude": "15 12 n",
    "longitude": "145 45 e",
    "un": "mp"
  },
  "mq": {
    "value": "mq",
    "name": "martinique",
    "names": [
      "martinique",
      "martinique",
      "martinique",
      "martinica"
    ],
    "region": "americas",
    "subregion": "caribbean",
    "currency": "eur",
    "alpha2": "mq",
    "alpha3": "mtq",
    "ioc": null,
    "number": "474",
    "tel": "596",
    "latitude": "",
    "longitude": "",
    "un": "mq"
  },
  "mr": {
    "value": "mr",
    "name": "mauritania",
    "names": [
      "mauritania",
      "mauretanien",
      "mauritanie",
      "mauritania"
    ],
    "region": "africa",
    "subregion": "western africa",
    "currency": "mro",
    "alpha2": "mr",
    "alpha3": "mrt",
    "ioc": "mtn",
    "number": "478",
    "tel": "222",
    "latitude": "20 00 n",
    "longitude": "12 00 w",
    "un": "mr"
  },
  "ms": {
    "value": "ms",
    "name": "montserrat",
    "names": [
      "montserrat",
      "montserrat",
      "montserrat",
      "montserrat"
    ],
    "region": "americas",
    "subregion": "caribbean",
    "currency": "xcd",
    "alpha2": "ms",
    "alpha3": "msr",
    "ioc": null,
    "number": "500",
    "tel": "1",
    "latitude": "16 45 n",
    "longitude": "62 12 w",
    "un": "ms"
  },
  "mt": {
    "value": "mt",
    "name": "malta",
    "names": [
      "malta",
      "malta",
      "malte",
      "malta"
    ],
    "region": "europe",
    "subregion": "southern europe",
    "currency": "eur",
    "alpha2": "mt",
    "alpha3": "mlt",
    "ioc": "mlt",
    "number": "470",
    "tel": "356",
    "latitude": "35 50 n",
    "longitude": "14 35 e",
    "un": "mt"
  },
  "mu": {
    "value": "mu",
    "name": "mauritius",
    "names": [
      "mauritius",
      "mauritius",
      "île maurice",
      "mauricio"
    ],
    "region": "africa",
    "subregion": "eastern africa",
    "currency": "mur",
    "alpha2": "mu",
    "alpha3": "mus",
    "ioc": "mri",
    "number": "480",
    "tel": "230",
    "latitude": "20 17 s",
    "longitude": "57 33 e",
    "un": "mu"
  },
  "mv": {
    "value": "mv",
    "name": "maldives",
    "names": [
      "maldives",
      "malediven",
      "maldivas"
    ],
    "region": "asia",
    "subregion": "southern asia",
    "currency": "mvr",
    "alpha2": "mv",
    "alpha3": "mdv",
    "ioc": "mdv",
    "number": "462",
    "tel": "960",
    "latitude": "3 15 n",
    "longitude": "73 00 e",
    "un": "mv"
  },
  "mw": {
    "value": "mw",
    "name": "malawi",
    "names": [
      "malawi"
    ],
    "region": "africa",
    "subregion": "eastern africa",
    "currency": "mwk",
    "alpha2": "mw",
    "alpha3": "mwi",
    "ioc": "maw",
    "number": "454",
    "tel": "265",
    "latitude": "13 30 s",
    "longitude": "34 00 e",
    "un": "mw"
  },
  "mx": {
    "value": "mx",
    "name": "mexico",
    "names": [
      "mexico",
      "mexiko",
      "mexique",
      "méxico"
    ],
    "region": "americas",
    "subregion": "central america",
    "currency": "mxn",
    "alpha2": "mx",
    "alpha3": "mex",
    "ioc": "mex",
    "number": "484",
    "tel": "52",
    "latitude": "23 00 n",
    "longitude": "102 00 w",
    "un": "mx"
  },
  "my": {
    "value": "my",
    "name": "malaysia",
    "names": [
      "malaysia",
      "malaisie",
      "malasia"
    ],
    "region": "asia",
    "subregion": "south-eastern asia",
    "currency": "myr",
    "alpha2": "my",
    "alpha3": "mys",
    "ioc": "mas",
    "number": "458",
    "tel": "60",
    "latitude": "2 30 n",
    "longitude": "112 30 e",
    "un": "my"
  },
  "mz": {
    "value": "mz",
    "name": "mozambique",
    "names": [
      "mozambique",
      "mosambik",
      "mozambique",
      "mozambique"
    ],
    "region": "africa",
    "subregion": "eastern africa",
    "currency": "mzn",
    "alpha2": "mz",
    "alpha3": "moz",
    "ioc": "moz",
    "number": "508",
    "tel": "258",
    "latitude": "18 15 s",
    "longitude": "35 00 e",
    "un": "mz"
  },
  "na": {
    "value": "na",
    "name": "namibia",
    "names": [
      "namibia",
      "namibia",
      "namibie",
      "namibia"
    ],
    "region": "africa",
    "subregion": "southern africa",
    "currency": "nad",
    "alpha2": "na",
    "alpha3": "nam",
    "ioc": "nam",
    "number": "516",
    "tel": "264",
    "latitude": "22 00 s",
    "longitude": "17 00 e",
    "un": "na"
  },
  "nc": {
    "value": "nc",
    "name": "new caledonia",
    "names": [
      "new caledonia",
      "neukaledonien",
      "nouvelle calédonie",
      "nueva caledonia"
    ],
    "region": "oceania",
    "subregion": "melanesia",
    "currency": "xpf",
    "alpha2": "nc",
    "alpha3": "ncl",
    "ioc": null,
    "number": "540",
    "tel": "687",
    "latitude": "21 30 s",
    "longitude": "165 30 e",
    "un": "nc"
  },
  "ne": {
    "value": "ne",
    "name": "niger",
    "names": [
      "níger"
    ],
    "region": "africa",
    "subregion": "western africa",
    "currency": "xof",
    "alpha2": "ne",
    "alpha3": "ner",
    "ioc": "nig",
    "number": "562",
    "tel": "227",
    "latitude": "16 00 n",
    "longitude": "8 00 e",
    "un": "ne"
  },
  "nf": {
    "value": "nf",
    "name": "norfolk island",
    "names": [
      "norfolk island",
      "norfolk island",
      "île de norfolk",
      "isla de norfolk"
    ],
    "region": "oceania",
    "subregion": "australia and new zealand",
    "currency": "aud",
    "alpha2": "nf",
    "alpha3": "nfk",
    "ioc": null,
    "number": "574",
    "tel": "672",
    "latitude": "29 02 s",
    "longitude": "167 57 e",
    "un": "nf"
  },
  "ng": {
    "value": "ng",
    "name": "nigeria",
    "names": [
      "nigeria",
      "nigéria",
      "the federal republic of nigeria"
    ],
    "region": "africa",
    "subregion": "western africa",
    "currency": "ngn",
    "alpha2": "ng",
    "alpha3": "nga",
    "ioc": "ngr",
    "number": "566",
    "tel": "234",
    "latitude": "10 00 n",
    "longitude": "8 00 e",
    "un": "ng"
  },
  "ni": {
    "value": "ni",
    "name": "nicaragua",
    "names": [
      "nicaragua",
      "nicaragua",
      "nicaragua",
      "nicaragua"
    ],
    "region": "americas",
    "subregion": "central america",
    "currency": "nio",
    "alpha2": "ni",
    "alpha3": "nic",
    "ioc": "nca",
    "number": "558",
    "tel": "505",
    "latitude": "13 00 n",
    "longitude": "85 00 w",
    "un": "ni"
  },
  "nl": {
    "value": "nl",
    "name": "netherlands",
    "names": [
      "netherlands",
      "niederlande",
      "pays-bas",
      "países bajos"
    ],
    "region": "europe",
    "subregion": "western europe",
    "currency": "eur",
    "alpha2": "nl",
    "alpha3": "nld",
    "ioc": "ned",
    "number": "528",
    "tel": "31",
    "latitude": "52 30 n",
    "longitude": "5 45 e",
    "un": "nl"
  },
  "no": {
    "value": "no",
    "name": "norway",
    "names": [
      "norway",
      "norwegen",
      "norvège",
      "noruega"
    ],
    "region": "europe",
    "subregion": "northern europe",
    "currency": "nok",
    "alpha2": "no",
    "alpha3": "nor",
    "ioc": "ned",
    "number": "578",
    "tel": "47",
    "latitude": "62 00 n",
    "longitude": "10 00 e",
    "un": "nl"
  },
  "np": {
    "value": "np",
    "name": "nepal",
    "names": [
      "nepal",
      "nepal",
      "népal",
      "nepal",
      "the federal democratic republic of nepal"
    ],
    "region": "asia",
    "subregion": "southern asia",
    "currency": "npr",
    "alpha2": "np",
    "alpha3": "npl",
    "ioc": "nep",
    "number": "524",
    "tel": "977",
    "latitude": "28 00 n",
    "longitude": "84 00 e",
    "un": "np"
  },
  "nr": {
    "value": "nr",
    "name": "nauru",
    "names": [
      "nauru",
      "nauru",
      "nauru",
      "nauru"
    ],
    "region": "oceania",
    "subregion": "micronesia",
    "currency": "aud",
    "alpha2": "nr",
    "alpha3": "nru",
    "ioc": "nru",
    "number": "520",
    "tel": "674",
    "latitude": "0 32 s",
    "longitude": "166 55 e",
    "un": "nr"
  },
  "nu": {
    "value": "nu",
    "name": "niue",
    "names": [
      "niue"
    ],
    "region": "oceania",
    "subregion": "polynesia",
    "currency": null,
    "alpha2": "nu",
    "alpha3": "niu",
    "ioc": null,
    "number": "570",
    "tel": "683",
    "latitude": "19 02 s",
    "longitude": "169 52 w",
    "un": "nu"
  },
  "nz": {
    "value": "nz",
    "name": "new zealand",
    "names": [
      "new zealand",
      "neuseeland",
      "nouvelle zã©lande",
      "nueva zelanda"
    ],
    "region": "oceania",
    "subregion": "australia and new zealand",
    "currency": "nzd",
    "alpha2": "nz",
    "alpha3": "nzl",
    "ioc": "nzl",
    "number": "554",
    "tel": "64",
    "latitude": "41 00 s",
    "longitude": "174 00 e",
    "un": "nz"
  },
  "om": {
    "value": "om",
    "name": "oman",
    "names": [
      "oman",
      "omán"
    ],
    "region": "asia",
    "subregion": "western asia",
    "currency": "omr",
    "alpha2": "om",
    "alpha3": "omn",
    "ioc": "oma",
    "number": "512",
    "tel": "968",
    "latitude": "21 00 n",
    "longitude": "57 00 e",
    "un": "om"
  },
  "pa": {
    "value": "pa",
    "name": "panama",
    "names": [
      "panama",
      "panamá"
    ],
    "region": "americas",
    "subregion": "central america",
    "currency": "pab",
    "alpha2": "pa",
    "alpha3": "pan",
    "ioc": "pan",
    "number": "591",
    "tel": "507",
    "latitude": "9 00 n",
    "longitude": "80 00 w",
    "un": "pa"
  },
  "pe": {
    "value": "pe",
    "name": "peru",
    "names": [
      "peru",
      "pérou",
      "perú"
    ],
    "region": "americas",
    "subregion": "south america",
    "currency": "pen",
    "alpha2": "pe",
    "alpha3": "per",
    "ioc": "per",
    "number": "604",
    "tel": "51",
    "latitude": "10 00 s",
    "longitude": "76 00 w",
    "un": "pe"
  },
  "pf": {
    "value": "pf",
    "name": "french polynesia",
    "names": [
      "french polynesia",
      "französisch-polynesien",
      "polynésie française",
      "polinesia francesa"
    ],
    "region": "oceania",
    "subregion": "polynesia",
    "currency": "xpf",
    "alpha2": "pf",
    "alpha3": "pyf",
    "ioc": null,
    "number": "258",
    "tel": "689",
    "latitude": "15 00 s",
    "longitude": "140 00 w",
    "un": "pf"
  },
  "pg": {
    "value": "pg",
    "name": "papua new guinea",
    "names": [
      "papua new guinea",
      "papua-neuguinea",
      "papouasie nouvelle-guinée",
      "papúa nueva guinea"
    ],
    "region": "oceania",
    "subregion": "melanesia",
    "currency": "pgk",
    "alpha2": "pg",
    "alpha3": "png",
    "ioc": "png",
    "number": "598",
    "tel": "675",
    "latitude": "6 00 s",
    "longitude": "147 00 e",
    "un": "pg"
  },
  "ph": {
    "value": "ph",
    "name": "philippines",
    "names": [
      "philippinen",
      "philippines",
      "filipinas"
    ],
    "region": "asia",
    "subregion": "south-eastern asia",
    "currency": "php",
    "alpha2": "ph",
    "alpha3": "phl",
    "ioc": "phi",
    "number": "608",
    "tel": "63",
    "latitude": "13 00 n",
    "longitude": "122 00 e",
    "un": "ph"
  },
  "pk": {
    "value": "pk",
    "name": "pakistan",
    "names": [
      "pakistan",
      "paquistán"
    ],
    "region": "asia",
    "subregion": "southern asia",
    "currency": "pkr",
    "alpha2": "pk",
    "alpha3": "pak",
    "ioc": "pak",
    "number": "586",
    "tel": "92",
    "latitude": "30 00 n",
    "longitude": "70 00 e",
    "un": "pk"
  },
  "pl": {
    "value": "pl",
    "name": "poland",
    "names": [
      "poland",
      "polen",
      "pologne",
      "polonia"
    ],
    "region": "europe",
    "subregion": "eastern europe",
    "currency": "pln",
    "alpha2": "pl",
    "alpha3": "pol",
    "ioc": "pol",
    "number": "616",
    "tel": "48",
    "latitude": "52 00 n",
    "longitude": "20 00 e",
    "un": "pl"
  },
  "pm": {
    "value": "pm",
    "name": "saint pierre and miquelon",
    "names": [
      "saint pierre and miquelon",
      "saint-pierre-et-miquelon",
      "saint-pierre-et-miquelon",
      "san pedro y miquelón"
    ],
    "region": "americas",
    "subregion": "northern america",
    "currency": "eur",
    "alpha2": "pm",
    "alpha3": "spm",
    "ioc": null,
    "number": "666",
    "tel": "508",
    "latitude": "46 50 n",
    "longitude": "56 20 w",
    "un": "pm"
  },
  "pn": {
    "value": "pn",
    "name": "pitcairn",
    "names": [
      "pitcairn"
    ],
    "region": "oceania",
    "subregion": "polynesia",
    "currency": "nzd",
    "alpha2": "pn",
    "alpha3": "pcn",
    "ioc": null,
    "number": "612",
    "tel": "",
    "latitude": "25 04 s",
    "longitude": "130 06 w",
    "un": "pn"
  },
  "pr": {
    "value": "pr",
    "name": "puerto rico",
    "names": [
      "puerto rico"
    ],
    "region": "americas",
    "subregion": "caribbean",
    "currency": "usd",
    "alpha2": "pr",
    "alpha3": "pri",
    "ioc": "pur",
    "number": "630",
    "tel": "1",
    "latitude": "18 15 n",
    "longitude": "66 30 w",
    "un": "pr"
  },
  "ps": {
    "value": "ps",
    "name": "palestinian territory, occupied",
    "names": [
      "palestine",
      "palästina",
      "palestine",
      "palestina",
      "the occupied palestinian territory"
    ],
    "region": "asia",
    "subregion": "western asia",
    "currency": null,
    "alpha2": "ps",
    "alpha3": "pse",
    "ioc": "ple",
    "number": "275",
    "tel": "970",
    "latitude": "",
    "longitude": "",
    "un": null
  },
  "pt": {
    "value": "pt",
    "name": "portugal",
    "names": [
      "portugal"
    ],
    "region": "europe",
    "subregion": "southern europe",
    "currency": "eur",
    "alpha2": "pt",
    "alpha3": "prt",
    "ioc": "por",
    "number": "620",
    "tel": "351",
    "latitude": "39 30 n",
    "longitude": "8 00 w",
    "un": "pt"
  },
  "pw": {
    "value": "pw",
    "name": "palau",
    "names": [
      "palau"
    ],
    "region": "oceania",
    "subregion": "micronesia",
    "currency": "usd",
    "alpha2": "pw",
    "alpha3": "plw",
    "ioc": "plw",
    "number": "585",
    "tel": "680",
    "latitude": "7 30 n",
    "longitude": "134 30 e",
    "un": "pw"
  },
  "py": {
    "value": "py",
    "name": "paraguay",
    "names": [
      "paraguay"
    ],
    "region": "americas",
    "subregion": "south america",
    "currency": "pyg",
    "alpha2": "py",
    "alpha3": "pry",
    "ioc": "par",
    "number": "600",
    "tel": "595",
    "latitude": "23 00 s",
    "longitude": "58 00 w",
    "un": "py"
  },
  "qa": {
    "value": "qa",
    "name": "qatar",
    "names": [
      "qatar",
      "katar"
    ],
    "region": "asia",
    "subregion": "western asia",
    "currency": "qar",
    "alpha2": "qa",
    "alpha3": "qat",
    "ioc": "qat",
    "number": "634",
    "tel": "974",
    "latitude": "25 30 n",
    "longitude": "51 15 e",
    "un": "qa"
  },
  "re": {
    "value": "re",
    "name": "réunion",
    "names": [
      "réunion",
      "réunion",
      "réunion",
      "reunión"
    ],
    "region": "africa",
    "subregion": "eastern africa",
    "currency": "eur",
    "alpha2": "re",
    "alpha3": "reu",
    "ioc": null,
    "number": "638",
    "tel": "262",
    "latitude": "",
    "longitude": "",
    "un": "re"
  },
  "ro": {
    "value": "ro",
    "name": "romania",
    "names": [
      "romania",
      "rumänien",
      "roumanie",
      "rumania"
    ],
    "region": "europe",
    "subregion": "eastern europe",
    "currency": "ron",
    "alpha2": "ro",
    "alpha3": "rou",
    "ioc": "rou",
    "number": "642",
    "tel": "40",
    "latitude": "46 00 n",
    "longitude": "25 00 e",
    "un": "ro"
  },
  "rs": {
    "value": "rs",
    "name": "serbia",
    "names": [
      "serbia",
      "serbien",
      "serbie",
      "serbia"
    ],
    "region": "europe",
    "subregion": "southern europe",
    "currency": "rsd",
    "alpha2": "rs",
    "alpha3": "srb",
    "ioc": "srb",
    "number": "688",
    "tel": "381",
    "latitude": "44 00 n",
    "longitude": "21 00 e",
    "un": "rs"
  },
  "ru": {
    "value": "ru",
    "name": "russian federation",
    "names": [
      "russia",
      "russland",
      "russie",
      "rusia"
    ],
    "region": "europe",
    "subregion": "eastern europe",
    "currency": "rub",
    "alpha2": "ru",
    "alpha3": "rus",
    "ioc": "rus",
    "number": "643",
    "tel": "7",
    "latitude": "60 00 n",
    "longitude": "100 00 e",
    "un": "ru"
  },
  "rw": {
    "value": "rw",
    "name": "rwanda",
    "names": [
      "rwanda",
      "ruanda"
    ],
    "region": "africa",
    "subregion": "eastern africa",
    "currency": "rwf",
    "alpha2": "rw",
    "alpha3": "rwa",
    "ioc": "rwa",
    "number": "646",
    "tel": "250",
    "latitude": "2 00 s",
    "longitude": "30 00 e",
    "un": "rw"
  },
  "sa": {
    "value": "sa",
    "name": "saudi arabia",
    "names": [
      "saudi arabia",
      "saudi-arabien",
      "arabie saoudite",
      "arabia saudí"
    ],
    "region": "asia",
    "subregion": "western asia",
    "currency": "sar",
    "alpha2": "sa",
    "alpha3": "sau",
    "ioc": "ksa",
    "number": "682",
    "tel": "966",
    "latitude": "25 00 n",
    "longitude": "45 00 e",
    "un": "sa"
  },
  "sb": {
    "value": "sb",
    "name": "solomon islands",
    "names": [
      "solomon islands",
      "salomonen",
      "îles salomon",
      "islas salomón"
    ],
    "region": "oceania",
    "subregion": "melanesia",
    "currency": "sbd",
    "alpha2": "sb",
    "alpha3": "slb",
    "ioc": "sol",
    "number": "090",
    "tel": "677",
    "latitude": "8 00 s",
    "longitude": "159 00 e",
    "un": "sb"
  },
  "sc": {
    "value": "sc",
    "name": "seychelles",
    "names": [
      "seychelles"
    ],
    "region": "africa",
    "subregion": "eastern africa",
    "currency": "scr",
    "alpha2": "sc",
    "alpha3": "syc",
    "ioc": "sey",
    "number": "690",
    "tel": "248",
    "latitude": "4 35 s",
    "longitude": "55 40 e",
    "un": "sc"
  },
  "sd": {
    "value": "sd",
    "name": "sudan",
    "names": [
      "sudan",
      "soudan",
      "sudán"
    ],
    "region": "africa",
    "subregion": "northern africa",
    "currency": "sdg",
    "alpha2": "sd",
    "alpha3": "sdn",
    "ioc": "sud",
    "number": "736",
    "tel": "249",
    "latitude": "15 00 n",
    "longitude": "30 00 e",
    "un": "sd"
  },
  "se": {
    "value": "se",
    "name": "sweden",
    "names": [
      "sweden",
      "schweden",
      "suède",
      "suecia"
    ],
    "region": "europe",
    "subregion": "northern europe",
    "currency": "sek",
    "alpha2": "se",
    "alpha3": "swe",
    "ioc": "swe",
    "number": "752",
    "tel": "46",
    "latitude": "62 00 n",
    "longitude": "15 00 e",
    "un": "se"
  },
  "sg": {
    "value": "sg",
    "name": "singapore",
    "names": [
      "singapore",
      "singapur",
      "singapour",
      "singapur"
    ],
    "region": "asia",
    "subregion": "south-eastern asia",
    "currency": "sgd",
    "alpha2": "sg",
    "alpha3": "sgp",
    "ioc": "sin",
    "number": "702",
    "tel": "65",
    "latitude": "1 22 n",
    "longitude": "103 48 e",
    "un": "sg"
  },
  "sh": {
    "value": "sh",
    "name": "saint helena",
    "names": [
      "saint helena",
      "sankt helena",
      "sainte hélène",
      "santa helena"
    ],
    "region": "africa",
    "subregion": "western africa",
    "currency": "shp",
    "alpha2": "sh",
    "alpha3": "shn",
    "ioc": null,
    "number": "654",
    "tel": "290",
    "latitude": "saint helena: 15 57 ",
    "longitude": "saint helena: 5 42 w",
    "un": "sh"
  },
  "si": {
    "value": "si",
    "name": "slovenia",
    "names": [
      "slovenia",
      "slowenien",
      "slovénie",
      "eslovenia"
    ],
    "region": "europe",
    "subregion": "southern europe",
    "currency": "eur",
    "alpha2": "si",
    "alpha3": "svn",
    "ioc": "slo",
    "number": "705",
    "tel": "386",
    "latitude": "46 07 n",
    "longitude": "14 49 e",
    "un": "si"
  },
  "sj": {
    "value": "sj",
    "name": "svalbard and jan mayen",
    "names": [
      "svalbard and jan mayen",
      "svalbard und jan mayen",
      "îles svalbard et jan mayen",
      "islas svalbard y jan mayen"
    ],
    "region": "europe",
    "subregion": "northern europe",
    "currency": "nok",
    "alpha2": "sj",
    "alpha3": "sjm",
    "ioc": null,
    "number": "744",
    "tel": "47",
    "latitude": "78 00 n",
    "longitude": "20 00 e",
    "un": "sj"
  },
  "sk": {
    "value": "sk",
    "name": "slovakia",
    "names": [
      "slovakia",
      "slowakei",
      "slovaquie",
      "república eslovaca"
    ],
    "region": "europe",
    "subregion": "eastern europe",
    "currency": "eur",
    "alpha2": "sk",
    "alpha3": "svk",
    "ioc": "svk",
    "number": "703",
    "tel": "421",
    "latitude": "48 40 n",
    "longitude": "19 30 e",
    "un": "sk"
  },
  "sl": {
    "value": "sl",
    "name": "sierra leone",
    "names": [
      "sierra leone"
    ],
    "region": "africa",
    "subregion": "western africa",
    "currency": "sll",
    "alpha2": "sl",
    "alpha3": "sle",
    "ioc": "sle",
    "number": "694",
    "tel": "232",
    "latitude": "8 30 n",
    "longitude": "11 30 w",
    "un": "sl"
  },
  "sm": {
    "value": "sm",
    "name": "san marino",
    "names": [
      "san marino",
      "saint-marin"
    ],
    "region": "europe",
    "subregion": "southern europe",
    "currency": "eur",
    "alpha2": "sm",
    "alpha3": "smr",
    "ioc": "smr",
    "number": "674",
    "tel": "378",
    "latitude": "43 46 n",
    "longitude": "12 25 e",
    "un": "sm"
  },
  "sn": {
    "value": "sn",
    "name": "senegal",
    "names": [
      "senegal",
      "sénégal"
    ],
    "region": "africa",
    "subregion": "western africa",
    "currency": "xof",
    "alpha2": "sn",
    "alpha3": "sen",
    "ioc": "sen",
    "number": "686",
    "tel": "221",
    "latitude": "14 00 n",
    "longitude": "14 00 w",
    "un": "sn"
  },
  "so": {
    "value": "so",
    "name": "somalia",
    "names": [
      "somalia"
    ],
    "region": "africa",
    "subregion": "eastern africa",
    "currency": "sos",
    "alpha2": "so",
    "alpha3": "som",
    "ioc": "som",
    "number": "706",
    "tel": "252",
    "latitude": "10 00 n",
    "longitude": "49 00 e",
    "un": "so"
  },
  "sr": {
    "value": "sr",
    "name": "suriname",
    "names": [
      "suriname",
      "surinam"
    ],
    "region": "americas",
    "subregion": "south america",
    "currency": "srd",
    "alpha2": "sr",
    "alpha3": "sur",
    "ioc": "sur",
    "number": "740",
    "tel": "597",
    "latitude": "4 00 n",
    "longitude": "56 00 w",
    "un": "sr"
  },
  "st": {
    "value": "st",
    "name": "sao tome and principe",
    "names": [
      "são tomé and príncipe",
      "são tomé und príncipe",
      "são tomé et príncipe",
      "santo tomé y príncipe"
    ],
    "region": "africa",
    "subregion": "middle africa",
    "currency": "std",
    "alpha2": "st",
    "alpha3": "stp",
    "ioc": "stp",
    "number": "678",
    "tel": "239",
    "latitude": "1 00 n",
    "longitude": "7 00 e",
    "un": "st"
  },
  "sv": {
    "value": "sv",
    "name": "el salvador",
    "names": [
      "salvador",
      "el salvador"
    ],
    "region": "americas",
    "subregion": "central america",
    "currency": "usd",
    "alpha2": "sv",
    "alpha3": "slv",
    "ioc": "esa",
    "number": "222",
    "tel": "503",
    "latitude": "13 50 n",
    "longitude": "88 55 w",
    "un": "sv"
  },
  "sy": {
    "value": "sy",
    "name": "syrian arab republic",
    "names": [
      "syria",
      "syrien",
      "syrie",
      "siria"
    ],
    "region": "asia",
    "subregion": "western asia",
    "currency": "syp",
    "alpha2": "sy",
    "alpha3": "syr",
    "ioc": "syr",
    "number": "760",
    "tel": "963",
    "latitude": "35 00 n",
    "longitude": "38 00 e",
    "un": "sy"
  },
  "sz": {
    "value": "sz",
    "name": "swaziland",
    "names": [
      "swaziland",
      "swasiland",
      "swaziland",
      "suazilandia"
    ],
    "region": "africa",
    "subregion": "southern africa",
    "currency": "szl",
    "alpha2": "sz",
    "alpha3": "swz",
    "ioc": "swz",
    "number": "748",
    "tel": "268",
    "latitude": "26 30 s",
    "longitude": "31 30 e",
    "un": "sz"
  },
  "tc": {
    "value": "tc",
    "name": "turks and caicos islands",
    "names": [
      "turks and caicos islands",
      "turks- und caicosinseln",
      "îles turks et caïcos",
      "islas turks y caicos"
    ],
    "region": "americas",
    "subregion": "caribbean",
    "currency": "usd",
    "alpha2": "tc",
    "alpha3": "tca",
    "ioc": null,
    "number": "796",
    "tel": "1",
    "latitude": "21 45 n",
    "longitude": "71 35 w",
    "un": "tc"
  },
  "td": {
    "value": "td",
    "name": "chad",
    "names": [
      "chad",
      "tschad",
      "tchad"
    ],
    "region": "africa",
    "subregion": "middle africa",
    "currency": "xaf",
    "alpha2": "td",
    "alpha3": "tcd",
    "ioc": "cha",
    "number": "148",
    "tel": "235",
    "latitude": "15 00 n",
    "longitude": "19 00 e",
    "un": "td"
  },
  "tf": {
    "value": "tf",
    "name": "french southern territories",
    "names": [
      "french southern territories",
      "französische südgebiete",
      "terres australes françaises",
      "territorios franceses del sur"
    ],
    "region": "",
    "subregion": "",
    "currency": "eur",
    "alpha2": "tf",
    "alpha3": "atf",
    "ioc": null,
    "number": "260",
    "tel": "",
    "latitude": "",
    "longitude": "",
    "un": null
  },
  "tg": {
    "value": "tg",
    "name": "togo",
    "names": [
      "togo"
    ],
    "region": "africa",
    "subregion": "western africa",
    "currency": "xof",
    "alpha2": "tg",
    "alpha3": "tgo",
    "ioc": "tog",
    "number": "768",
    "tel": "228",
    "latitude": "8 00 n",
    "longitude": "1 10 e",
    "un": "tg"
  },
  "th": {
    "value": "th",
    "name": "thailand",
    "names": [
      "thailand",
      "thailand",
      "thaïlande",
      "tailandia"
    ],
    "region": "asia",
    "subregion": "south-eastern asia",
    "currency": "thb",
    "alpha2": "th",
    "alpha3": "tha",
    "ioc": "tha",
    "number": "764",
    "tel": "66",
    "latitude": "15 00 n",
    "longitude": "100 00 e",
    "un": "th"
  },
  "tj": {
    "value": "tj",
    "name": "tajikistan",
    "names": [
      "tajikistan",
      "tadschikistan",
      "tajikistan",
      "tayikistán"
    ],
    "region": "asia",
    "subregion": "central asia",
    "currency": "tjs",
    "alpha2": "tj",
    "alpha3": "tjk",
    "ioc": "tjk",
    "number": "762",
    "tel": "992",
    "latitude": "39 00 n",
    "longitude": "71 00 e",
    "un": "tj"
  },
  "tk": {
    "value": "tk",
    "name": "tokelau",
    "names": [
      "tokelau",
      "tokelau",
      "îles tokelau",
      "islas tokelau"
    ],
    "region": "oceania",
    "subregion": "polynesia",
    "currency": "nzd",
    "alpha2": "tk",
    "alpha3": "tkl",
    "ioc": null,
    "number": "772",
    "tel": "690",
    "latitude": "9 00 s",
    "longitude": "172 00 w",
    "un": "tk"
  },
  "tl": {
    "value": "tl",
    "name": "timor-leste",
    "names": [
      "east timor",
      "ost-timor",
      "timor oriental",
      "timor oriental"
    ],
    "region": "asia",
    "subregion": "south-eastern asia",
    "currency": "idr",
    "alpha2": "tl",
    "alpha3": "tls",
    "ioc": null,
    "number": "626",
    "tel": "670",
    "latitude": "8 50 s",
    "longitude": "125 55 e",
    "un": null
  },
  "tm": {
    "value": "tm",
    "name": "turkmenistan",
    "names": [
      "turkmenistan",
      "turkmenistan",
      "turkménistan",
      "turkmenistán"
    ],
    "region": "asia",
    "subregion": "central asia",
    "currency": "tmt",
    "alpha2": "tm",
    "alpha3": "tkm",
    "ioc": "tkm",
    "number": "795",
    "tel": "993",
    "latitude": "40 00 n",
    "longitude": "60 00 e",
    "un": "tm"
  },
  "tn": {
    "value": "tn",
    "name": "tunisia",
    "names": [
      "tunisia",
      "tunesien",
      "tunisie",
      "túnez"
    ],
    "region": "africa",
    "subregion": "northern africa",
    "currency": "tnd",
    "alpha2": "tn",
    "alpha3": "tun",
    "ioc": "tun",
    "number": "788",
    "tel": "216",
    "latitude": "34 00 n",
    "longitude": "9 00 e",
    "un": "tn"
  },
  "to": {
    "value": "to",
    "name": "tonga",
    "names": [
      "tonga"
    ],
    "region": "oceania",
    "subregion": "polynesia",
    "currency": "top",
    "alpha2": "to",
    "alpha3": "ton",
    "ioc": "tga",
    "number": "776",
    "tel": "676",
    "latitude": "20 00 s",
    "longitude": "175 00 w",
    "un": "to"
  },
  "tr": {
    "value": "tr",
    "name": "turkey",
    "names": [
      "turkey",
      "türkei",
      "turquie",
      "turquía"
    ],
    "region": "asia",
    "subregion": "western asia",
    "currency": "try",
    "alpha2": "tr",
    "alpha3": "tur",
    "ioc": "tur",
    "number": "792",
    "tel": "90",
    "latitude": "39 00 n",
    "longitude": "35 00 e",
    "un": "tr"
  },
  "tt": {
    "value": "tt",
    "name": "trinidad and tobago",
    "names": [
      "trinidad and tobago",
      "trinidad und tobago",
      "trinité et tobago",
      "trinidad y tobago"
    ],
    "region": "americas",
    "subregion": "caribbean",
    "currency": "ttd",
    "alpha2": "tt",
    "alpha3": "tto",
    "ioc": "tri",
    "number": "780",
    "tel": "1",
    "latitude": "11 00 n",
    "longitude": "61 00 w",
    "un": "tt"
  },
  "tv": {
    "value": "tv",
    "name": "tuvalu",
    "names": [
      "tuvalu",
      "tuvalu",
      "tuvalu",
      "tuvalu"
    ],
    "region": "oceania",
    "subregion": "polynesia",
    "currency": "tvd",
    "alpha2": "tv",
    "alpha3": "tuv",
    "ioc": "tuv",
    "number": "798",
    "tel": "688",
    "latitude": "8 00 s",
    "longitude": "178 00 e",
    "un": "tv"
  },
  "tw": {
    "value": "tw",
    "name": "taiwan, province of china",
    "names": [
      "taiwan",
      "taiwán"
    ],
    "region": "asia",
    "subregion": "eastern asia",
    "currency": "twd",
    "alpha2": "tw",
    "alpha3": "twn",
    "ioc": "tpe",
    "number": "158",
    "tel": "886",
    "latitude": "23 30 n",
    "longitude": "121 00 e",
    "un": "tw",
    "commonname": "taiwan"
  },
  "tz": {
    "value": "tz",
    "name": "tanzania, united republic of",
    "names": [
      "tanzania",
      "tansania",
      "tanzanie"
    ],
    "region": "africa",
    "subregion": "eastern africa",
    "currency": "tzs",
    "alpha2": "tz",
    "alpha3": "tza",
    "ioc": "tan",
    "number": "834",
    "tel": "255",
    "latitude": "6 00 s",
    "longitude": "35 00 e",
    "un": "tz",
    "commonname": "tanzania"
  },
  "ua": {
    "value": "ua",
    "name": "ukraine",
    "names": [
      "ukraine",
      "ukraine",
      "ukraine",
      "ucrania"
    ],
    "region": "europe",
    "subregion": "eastern europe",
    "currency": "uah",
    "alpha2": "ua",
    "alpha3": "ukr",
    "ioc": "ukr",
    "number": "804",
    "tel": "380",
    "latitude": "49 00 n",
    "longitude": "32 00 e",
    "un": "ua"
  },
  "ug": {
    "value": "ug",
    "name": "uganda",
    "names": [
      "uganda"
    ],
    "region": "africa",
    "subregion": "eastern africa",
    "currency": "ugx",
    "alpha2": "ug",
    "alpha3": "uga",
    "ioc": "uga",
    "number": "800",
    "tel": "256",
    "latitude": "1 00 n",
    "longitude": "32 00 e",
    "un": "ug"
  },
  "um": {
    "value": "um",
    "name": "united states minor outlying islands",
    "names": [
      "united states minor outlying islands",
      "us-amerikanische hoheitsgebiete",
      "dépendances américaines",
      "islas menores de estados unidos"
    ],
    "region": "americas",
    "subregion": "northern america",
    "currency": "usd",
    "alpha2": "um",
    "alpha3": "umi",
    "ioc": null,
    "number": "581",
    "tel": "",
    "latitude": "",
    "longitude": "",
    "un": "um"
  },
  "us": {
    "value": "us",
    "name": "united states",
    "names": [
      "united states of america",
      "vereinigte staaten von amerika",
      "états-unis",
      "estados unidos"
    ],
    "region": "americas",
    "subregion": "northern america",
    "currency": "usd",
    "alpha2": "us",
    "alpha3": "usa",
    "ioc": "usa",
    "number": "840",
    "tel": "1",
    "latitude": "38 00 n",
    "longitude": "97 00 w",
    "un": "us"
  },
  "uy": {
    "value": "uy",
    "name": "uruguay",
    "names": [
      "uruguay"
    ],
    "region": "americas",
    "subregion": "south america",
    "currency": "uyu",
    "alpha2": "uy",
    "alpha3": "ury",
    "ioc": "uru",
    "number": "858",
    "tel": "598",
    "latitude": "33 00 s",
    "longitude": "56 00 w",
    "un": "uy"
  },
  "uz": {
    "value": "uz",
    "name": "uzbekistan",
    "names": [
      "uzbekistan",
      "usbekistan",
      "ouzbékistan",
      "uzbekistán"
    ],
    "region": "asia",
    "subregion": "central asia",
    "currency": "uzs",
    "alpha2": "uz",
    "alpha3": "uzb",
    "ioc": "uzb",
    "number": "860",
    "tel": "998",
    "latitude": "41 00 n",
    "longitude": "64 00 e",
    "un": "uz"
  },
  "va": {
    "value": "va",
    "name": "holy see (vatican city state)",
    "names": [
      "vatican city",
      "vatikan",
      "cité du vatican",
      "ciudad del vaticano"
    ],
    "region": "europe",
    "subregion": "southern europe",
    "currency": "eur",
    "alpha2": "va",
    "alpha3": "vat",
    "ioc": null,
    "number": "336",
    "tel": "39",
    "latitude": "41 54 n",
    "longitude": "12 27 e",
    "un": "va"
  },
  "vc": {
    "value": "vc",
    "name": "saint vincent and the grenedines",
    "names": [
      "saint vincent and the grenadines",
      "saint vincent und die grenadinen",
      "saint-vincent et les grenadines",
      "san vicente y granadinas"
    ],
    "region": "americas",
    "subregion": "caribbean",
    "currency": "xcd",
    "alpha2": "vc",
    "alpha3": "vct",
    "ioc": "vin",
    "number": "670",
    "tel": "1",
    "latitude": "13 15 n",
    "longitude": "61 12 w",
    "un": "vc"
  },
  "ve": {
    "value": "ve",
    "name": "venezuela, bolivarian republic of",
    "names": [
      "venezuela"
    ],
    "region": "americas",
    "subregion": "south america",
    "currency": "vef",
    "alpha2": "ve",
    "alpha3": "ven",
    "ioc": "ven",
    "number": "862",
    "tel": "58",
    "latitude": "8 00 n",
    "longitude": "66 00 w",
    "un": "ve",
    "commonname": "venezuela"
  },
  "vg": {
    "value": "vg",
    "name": "virgin islands, british",
    "names": [
      "british virgin islands",
      "britische jungferninseln",
      "îles vierges britanniques",
      "islas vírgenes del reino unido"
    ],
    "region": "americas",
    "subregion": "caribbean",
    "currency": "usd",
    "alpha2": "vg",
    "alpha3": "vgb",
    "ioc": "ivb",
    "number": "092",
    "tel": "1",
    "latitude": "",
    "longitude": "",
    "un": "vg"
  },
  "vi": {
    "value": "vi",
    "name": "virgin islands, u.s.",
    "names": [
      "virgin islands of the united states",
      "amerikanische jungferninseln",
      "îles vierges américaines",
      "islas vírgenes de los estados unidos"
    ],
    "region": "americas",
    "subregion": "caribbean",
    "currency": "usd",
    "alpha2": "vi",
    "alpha3": "vir",
    "ioc": "isv",
    "number": "850",
    "tel": "1",
    "latitude": "",
    "longitude": "",
    "un": "vi"
  },
  "vn": {
    "value": "vn",
    "name": "viet nam",
    "names": [
      "vietnam"
    ],
    "region": "asia",
    "subregion": "south-eastern asia",
    "currency": "vnd",
    "alpha2": "vn",
    "alpha3": "vnm",
    "ioc": "vie",
    "number": "704",
    "tel": "84",
    "latitude": "16 10 n",
    "longitude": "107 50 e",
    "un": "vn"
  },
  "vu": {
    "value": "vu",
    "name": "vanuatu",
    "names": [
      "vanuatu"
    ],
    "region": "oceania",
    "subregion": "melanesia",
    "currency": null,
    "alpha2": "vu",
    "alpha3": "vut",
    "ioc": "van",
    "number": "548",
    "tel": "678",
    "latitude": "16 00 s",
    "longitude": "167 00 e",
    "un": "vu"
  },
  "wf": {
    "value": "wf",
    "name": "wallis and futuna",
    "names": [
      "wallis and futuna",
      "wallis und futuna",
      "wallis et futuna",
      "wallis y futuna"
    ],
    "region": "oceania",
    "subregion": "polynesia",
    "currency": "xpf",
    "alpha2": "wf",
    "alpha3": "wlf",
    "ioc": null,
    "number": "876",
    "tel": "681",
    "latitude": "13 18 s",
    "longitude": "176 12 w",
    "un": "wf"
  },
  "ws": {
    "value": "ws",
    "name": "samoa",
    "names": [
      "samoa"
    ],
    "region": "oceania",
    "subregion": "polynesia",
    "currency": "usd",
    "alpha2": "ws",
    "alpha3": "wsm",
    "ioc": "sam",
    "number": "882",
    "tel": "685",
    "latitude": "13 35 s",
    "longitude": "172 20 w",
    "un": "ws"
  },
  "ye": {
    "value": "ye",
    "name": "yemen",
    "names": [
      "yemen",
      "jemen",
      "yémen"
    ],
    "region": "asia",
    "subregion": "western asia",
    "currency": "yer",
    "alpha2": "ye",
    "alpha3": "yem",
    "ioc": "yem",
    "number": "887",
    "tel": "967",
    "latitude": "15 00 n",
    "longitude": "48 00 e",
    "un": "ye"
  },
  "yt": {
    "value": "yt",
    "name": "mayotte",
    "names": [
      "mayotte",
      "mayotte",
      "mayotte",
      "mayotte"
    ],
    "region": "africa",
    "subregion": "eastern africa",
    "currency": "eur",
    "alpha2": "yt",
    "alpha3": "myt",
    "ioc": null,
    "number": "175",
    "tel": "269",
    "latitude": "12 50 s",
    "longitude": "45 10 e",
    "un": "yt"
  },
  "za": {
    "value": "za",
    "name": "south africa",
    "names": [
      "south africa",
      "republik südafrika",
      "afrique du sud",
      "república de sudáfrica"
    ],
    "region": "africa",
    "subregion": "southern africa",
    "currency": "zar",
    "alpha2": "za",
    "alpha3": "zaf",
    "ioc": "rsa",
    "number": "710",
    "tel": "27",
    "latitude": "29 00 s",
    "longitude": "24 00 e",
    "un": "za"
  },
  "zm": {
    "value": "zm",
    "name": "zambia",
    "names": [
      "zambia",
      "sambia",
      "zambie"
    ],
    "region": "africa",
    "subregion": "eastern africa",
    "currency": "zmk",
    "alpha2": "zm",
    "alpha3": "zmb",
    "ioc": "zam",
    "number": "894",
    "tel": "260",
    "latitude": "15 00 s",
    "longitude": "30 00 e",
    "un": "zm"
  },
  "zw": {
    "value": "zw",
    "name": "zimbabwe",
    "names": [
      "zimbabwe",
      "simbabwe",
      "zimbabue"
    ],
    "region": "africa",
    "subregion": "eastern africa",
    "currency": "zwd",
    "alpha2": "zw",
    "alpha3": "zwe",
    "ioc": "zim",
    "number": "716",
    "tel": "263",
    "latitude": "20 00 s",
    "longitude": "30 00 e",
    "un": "zw"
  }
};

  iso.currencies = {
  "eur": {
    "value": "eur",
    "name": "eur",
    "countries": [
      "ad",
      "at",
      "be",
      "cy",
      "de",
      "es",
      "fi",
      "fr",
      "gf",
      "gp",
      "gr",
      "ie",
      "it",
      "lu",
      "mc",
      "me",
      "mf",
      "mq",
      "mt",
      "nl",
      "pm",
      "pt",
      "re",
      "si",
      "sk",
      "sm",
      "tf",
      "va",
      "yt"
    ]
  },
  "aed": {
    "value": "aed",
    "name": "aed",
    "countries": [
      "ae"
    ]
  },
  "afn": {
    "value": "afn",
    "name": "afn",
    "countries": [
      "af"
    ]
  },
  "xcd": {
    "value": "xcd",
    "name": "xcd",
    "countries": [
      "ag",
      "ai",
      "dm",
      "gd",
      "kn",
      "lc",
      "ms",
      "vc"
    ]
  },
  "all": {
    "value": "all",
    "name": "all",
    "countries": [
      "al"
    ]
  },
  "amd": {
    "value": "amd",
    "name": "amd",
    "countries": [
      "am"
    ]
  },
  "ang": {
    "value": "ang",
    "name": "ang",
    "countries": [
      "an"
    ]
  },
  "aoa": {
    "value": "aoa",
    "name": "aoa",
    "countries": [
      "ao"
    ]
  },
  "null": {
    "value": null,
    "name": null,
    "countries": [
      "aq",
      "ax",
      "bl",
      "cd",
      "cg",
      "gq",
      "gs",
      "mg",
      "mk",
      "nu",
      "ps",
      "vu"
    ]
  },
  "ars": {
    "value": "ars",
    "name": "ars",
    "countries": [
      "ar"
    ]
  },
  "usd": {
    "value": "usd",
    "name": "usd",
    "countries": [
      "as",
      "ec",
      "fj",
      "fm",
      "gu",
      "ht",
      "io",
      "mh",
      "mp",
      "pr",
      "pw",
      "sv",
      "tc",
      "um",
      "us",
      "vg",
      "vi",
      "ws"
    ]
  },
  "aud": {
    "value": "aud",
    "name": "aud",
    "countries": [
      "au",
      "cc",
      "cx",
      "hm",
      "ki",
      "nf",
      "nr"
    ]
  },
  "awg": {
    "value": "awg",
    "name": "awg",
    "countries": [
      "aw"
    ]
  },
  "azn": {
    "value": "azn",
    "name": "azn",
    "countries": [
      "az"
    ]
  },
  "bam": {
    "value": "bam",
    "name": "bam",
    "countries": [
      "ba"
    ]
  },
  "bbd": {
    "value": "bbd",
    "name": "bbd",
    "countries": [
      "bb"
    ]
  },
  "btd": {
    "value": "btd",
    "name": "btd",
    "countries": [
      "bd"
    ]
  },
  "xof": {
    "value": "xof",
    "name": "xof",
    "countries": [
      "bf",
      "bj",
      "ci",
      "gw",
      "ml",
      "ne",
      "sn",
      "tg"
    ]
  },
  "bgn": {
    "value": "bgn",
    "name": "bgn",
    "countries": [
      "bg"
    ]
  },
  "bhd": {
    "value": "bhd",
    "name": "bhd",
    "countries": [
      "bh"
    ]
  },
  "bif": {
    "value": "bif",
    "name": "bif",
    "countries": [
      "bi"
    ]
  },
  "bmd": {
    "value": "bmd",
    "name": "bmd",
    "countries": [
      "bm"
    ]
  },
  "bnd": {
    "value": "bnd",
    "name": "bnd",
    "countries": [
      "bn"
    ]
  },
  "bob": {
    "value": "bob",
    "name": "bob",
    "countries": [
      "bo"
    ]
  },
  "brl": {
    "value": "brl",
    "name": "brl",
    "countries": [
      "br"
    ]
  },
  "bsd": {
    "value": "bsd",
    "name": "bsd",
    "countries": [
      "bs"
    ]
  },
  "btn": {
    "value": "btn",
    "name": "btn",
    "countries": [
      "bt"
    ]
  },
  "nok": {
    "value": "nok",
    "name": "nok",
    "countries": [
      "bv",
      "no",
      "sj"
    ]
  },
  "bwp": {
    "value": "bwp",
    "name": "bwp",
    "countries": [
      "bw"
    ]
  },
  "byr": {
    "value": "byr",
    "name": "byr",
    "countries": [
      "by"
    ]
  },
  "bzd": {
    "value": "bzd",
    "name": "bzd",
    "countries": [
      "bz"
    ]
  },
  "cad": {
    "value": "cad",
    "name": "cad",
    "countries": [
      "ca"
    ]
  },
  "xaf": {
    "value": "xaf",
    "name": "xaf",
    "countries": [
      "cf",
      "cm",
      "ga",
      "td"
    ]
  },
  "chf": {
    "value": "chf",
    "name": "chf",
    "countries": [
      "ch",
      "li"
    ]
  },
  "nzd": {
    "value": "nzd",
    "name": "nzd",
    "countries": [
      "ck",
      "nz",
      "pn",
      "tk"
    ]
  },
  "clp": {
    "value": "clp",
    "name": "clp",
    "countries": [
      "cl"
    ]
  },
  "cny": {
    "value": "cny",
    "name": "cny",
    "countries": [
      "cn"
    ]
  },
  "cop": {
    "value": "cop",
    "name": "cop",
    "countries": [
      "co"
    ]
  },
  "crc": {
    "value": "crc",
    "name": "crc",
    "countries": [
      "cr"
    ]
  },
  "cup": {
    "value": "cup",
    "name": "cup",
    "countries": [
      "cu"
    ]
  },
  "cve": {
    "value": "cve",
    "name": "cve",
    "countries": [
      "cv"
    ]
  },
  "czk": {
    "value": "czk",
    "name": "czk",
    "countries": [
      "cz"
    ]
  },
  "djf": {
    "value": "djf",
    "name": "djf",
    "countries": [
      "dj"
    ]
  },
  "dkk": {
    "value": "dkk",
    "name": "dkk",
    "countries": [
      "dk",
      "fo",
      "gl"
    ]
  },
  "dop": {
    "value": "dop",
    "name": "dop",
    "countries": [
      "do"
    ]
  },
  "dzd": {
    "value": "dzd",
    "name": "dzd",
    "countries": [
      "dz"
    ]
  },
  "eek": {
    "value": "eek",
    "name": "eek",
    "countries": [
      "ee"
    ]
  },
  "egp": {
    "value": "egp",
    "name": "egp",
    "countries": [
      "eg"
    ]
  },
  "mad": {
    "value": "mad",
    "name": "mad",
    "countries": [
      "eh",
      "ma"
    ]
  },
  "etb": {
    "value": "etb",
    "name": "etb",
    "countries": [
      "er",
      "et"
    ]
  },
  "fkp": {
    "value": "fkp",
    "name": "fkp",
    "countries": [
      "fk"
    ]
  },
  "gbp": {
    "value": "gbp",
    "name": "gbp",
    "countries": [
      "gb"
    ]
  },
  "gel": {
    "value": "gel",
    "name": "gel",
    "countries": [
      "ge"
    ]
  },
  "ggp": {
    "value": "ggp",
    "name": "ggp",
    "countries": [
      "gg"
    ]
  },
  "ghs": {
    "value": "ghs",
    "name": "ghs",
    "countries": [
      "gh"
    ]
  },
  "gip": {
    "value": "gip",
    "name": "gip",
    "countries": [
      "gi"
    ]
  },
  "gmd": {
    "value": "gmd",
    "name": "gmd",
    "countries": [
      "gm"
    ]
  },
  "gnf": {
    "value": "gnf",
    "name": "gnf",
    "countries": [
      "gn"
    ]
  },
  "gtq": {
    "value": "gtq",
    "name": "gtq",
    "countries": [
      "gt"
    ]
  },
  "gyd": {
    "value": "gyd",
    "name": "gyd",
    "countries": [
      "gy"
    ]
  },
  "hkd": {
    "value": "hkd",
    "name": "hkd",
    "countries": [
      "hk"
    ]
  },
  "hnl": {
    "value": "hnl",
    "name": "hnl",
    "countries": [
      "hn"
    ]
  },
  "hrk": {
    "value": "hrk",
    "name": "hrk",
    "countries": [
      "hr"
    ]
  },
  "huf": {
    "value": "huf",
    "name": "huf",
    "countries": [
      "hu"
    ]
  },
  "idr": {
    "value": "idr",
    "name": "idr",
    "countries": [
      "id",
      "tl"
    ]
  },
  "ils": {
    "value": "ils",
    "name": "ils",
    "countries": [
      "il"
    ]
  },
  "imp": {
    "value": "imp",
    "name": "imp",
    "countries": [
      "im"
    ]
  },
  "inr": {
    "value": "inr",
    "name": "inr",
    "countries": [
      "in"
    ]
  },
  "iqd": {
    "value": "iqd",
    "name": "iqd",
    "countries": [
      "iq"
    ]
  },
  "irr": {
    "value": "irr",
    "name": "irr",
    "countries": [
      "ir"
    ]
  },
  "isk": {
    "value": "isk",
    "name": "isk",
    "countries": [
      "is"
    ]
  },
  "jep": {
    "value": "jep",
    "name": "jep",
    "countries": [
      "je"
    ]
  },
  "jmd": {
    "value": "jmd",
    "name": "jmd",
    "countries": [
      "jm"
    ]
  },
  "jod": {
    "value": "jod",
    "name": "jod",
    "countries": [
      "jo"
    ]
  },
  "jpy": {
    "value": "jpy",
    "name": "jpy",
    "countries": [
      "jp"
    ]
  },
  "kes": {
    "value": "kes",
    "name": "kes",
    "countries": [
      "ke"
    ]
  },
  "kgs": {
    "value": "kgs",
    "name": "kgs",
    "countries": [
      "kg"
    ]
  },
  "khr": {
    "value": "khr",
    "name": "khr",
    "countries": [
      "kh"
    ]
  },
  "kmf": {
    "value": "kmf",
    "name": "kmf",
    "countries": [
      "km"
    ]
  },
  "kpw": {
    "value": "kpw",
    "name": "kpw",
    "countries": [
      "kp"
    ]
  },
  "krw": {
    "value": "krw",
    "name": "krw",
    "countries": [
      "kr"
    ]
  },
  "kwd": {
    "value": "kwd",
    "name": "kwd",
    "countries": [
      "kw"
    ]
  },
  "kyd": {
    "value": "kyd",
    "name": "kyd",
    "countries": [
      "ky"
    ]
  },
  "kzt": {
    "value": "kzt",
    "name": "kzt",
    "countries": [
      "kz"
    ]
  },
  "lak": {
    "value": "lak",
    "name": "lak",
    "countries": [
      "la"
    ]
  },
  "lbp": {
    "value": "lbp",
    "name": "lbp",
    "countries": [
      "lb"
    ]
  },
  "lkr": {
    "value": "lkr",
    "name": "lkr",
    "countries": [
      "lk"
    ]
  },
  "lrd": {
    "value": "lrd",
    "name": "lrd",
    "countries": [
      "lr"
    ]
  },
  "lsl": {
    "value": "lsl",
    "name": "lsl",
    "countries": [
      "ls"
    ]
  },
  "ltl": {
    "value": "ltl",
    "name": "ltl",
    "countries": [
      "lt"
    ]
  },
  "lvl": {
    "value": "lvl",
    "name": "lvl",
    "countries": [
      "lv"
    ]
  },
  "lyd": {
    "value": "lyd",
    "name": "lyd",
    "countries": [
      "ly"
    ]
  },
  "mdl": {
    "value": "mdl",
    "name": "mdl",
    "countries": [
      "md"
    ]
  },
  "mnk": {
    "value": "mnk",
    "name": "mnk",
    "countries": [
      "mm"
    ]
  },
  "mnt": {
    "value": "mnt",
    "name": "mnt",
    "countries": [
      "mn"
    ]
  },
  "mop": {
    "value": "mop",
    "name": "mop",
    "countries": [
      "mo"
    ]
  },
  "mro": {
    "value": "mro",
    "name": "mro",
    "countries": [
      "mr"
    ]
  },
  "mur": {
    "value": "mur",
    "name": "mur",
    "countries": [
      "mu"
    ]
  },
  "mvr": {
    "value": "mvr",
    "name": "mvr",
    "countries": [
      "mv"
    ]
  },
  "mwk": {
    "value": "mwk",
    "name": "mwk",
    "countries": [
      "mw"
    ]
  },
  "mxn": {
    "value": "mxn",
    "name": "mxn",
    "countries": [
      "mx"
    ]
  },
  "myr": {
    "value": "myr",
    "name": "myr",
    "countries": [
      "my"
    ]
  },
  "mzn": {
    "value": "mzn",
    "name": "mzn",
    "countries": [
      "mz"
    ]
  },
  "nad": {
    "value": "nad",
    "name": "nad",
    "countries": [
      "na"
    ]
  },
  "xpf": {
    "value": "xpf",
    "name": "xpf",
    "countries": [
      "nc",
      "pf",
      "wf"
    ]
  },
  "ngn": {
    "value": "ngn",
    "name": "ngn",
    "countries": [
      "ng"
    ]
  },
  "nio": {
    "value": "nio",
    "name": "nio",
    "countries": [
      "ni"
    ]
  },
  "npr": {
    "value": "npr",
    "name": "npr",
    "countries": [
      "np"
    ]
  },
  "omr": {
    "value": "omr",
    "name": "omr",
    "countries": [
      "om"
    ]
  },
  "pab": {
    "value": "pab",
    "name": "pab",
    "countries": [
      "pa"
    ]
  },
  "pen": {
    "value": "pen",
    "name": "pen",
    "countries": [
      "pe"
    ]
  },
  "pgk": {
    "value": "pgk",
    "name": "pgk",
    "countries": [
      "pg"
    ]
  },
  "php": {
    "value": "php",
    "name": "php",
    "countries": [
      "ph"
    ]
  },
  "pkr": {
    "value": "pkr",
    "name": "pkr",
    "countries": [
      "pk"
    ]
  },
  "pln": {
    "value": "pln",
    "name": "pln",
    "countries": [
      "pl"
    ]
  },
  "pyg": {
    "value": "pyg",
    "name": "pyg",
    "countries": [
      "py"
    ]
  },
  "qar": {
    "value": "qar",
    "name": "qar",
    "countries": [
      "qa"
    ]
  },
  "ron": {
    "value": "ron",
    "name": "ron",
    "countries": [
      "ro"
    ]
  },
  "rsd": {
    "value": "rsd",
    "name": "rsd",
    "countries": [
      "rs"
    ]
  },
  "rub": {
    "value": "rub",
    "name": "rub",
    "countries": [
      "ru"
    ]
  },
  "rwf": {
    "value": "rwf",
    "name": "rwf",
    "countries": [
      "rw"
    ]
  },
  "sar": {
    "value": "sar",
    "name": "sar",
    "countries": [
      "sa"
    ]
  },
  "sbd": {
    "value": "sbd",
    "name": "sbd",
    "countries": [
      "sb"
    ]
  },
  "scr": {
    "value": "scr",
    "name": "scr",
    "countries": [
      "sc"
    ]
  },
  "sdg": {
    "value": "sdg",
    "name": "sdg",
    "countries": [
      "sd"
    ]
  },
  "sek": {
    "value": "sek",
    "name": "sek",
    "countries": [
      "se"
    ]
  },
  "sgd": {
    "value": "sgd",
    "name": "sgd",
    "countries": [
      "sg"
    ]
  },
  "shp": {
    "value": "shp",
    "name": "shp",
    "countries": [
      "sh"
    ]
  },
  "sll": {
    "value": "sll",
    "name": "sll",
    "countries": [
      "sl"
    ]
  },
  "sos": {
    "value": "sos",
    "name": "sos",
    "countries": [
      "so"
    ]
  },
  "srd": {
    "value": "srd",
    "name": "srd",
    "countries": [
      "sr"
    ]
  },
  "std": {
    "value": "std",
    "name": "std",
    "countries": [
      "st"
    ]
  },
  "syp": {
    "value": "syp",
    "name": "syp",
    "countries": [
      "sy"
    ]
  },
  "szl": {
    "value": "szl",
    "name": "szl",
    "countries": [
      "sz"
    ]
  },
  "thb": {
    "value": "thb",
    "name": "thb",
    "countries": [
      "th"
    ]
  },
  "tjs": {
    "value": "tjs",
    "name": "tjs",
    "countries": [
      "tj"
    ]
  },
  "tmt": {
    "value": "tmt",
    "name": "tmt",
    "countries": [
      "tm"
    ]
  },
  "tnd": {
    "value": "tnd",
    "name": "tnd",
    "countries": [
      "tn"
    ]
  },
  "top": {
    "value": "top",
    "name": "top",
    "countries": [
      "to"
    ]
  },
  "try": {
    "value": "try",
    "name": "try",
    "countries": [
      "tr"
    ]
  },
  "ttd": {
    "value": "ttd",
    "name": "ttd",
    "countries": [
      "tt"
    ]
  },
  "tvd": {
    "value": "tvd",
    "name": "tvd",
    "countries": [
      "tv"
    ]
  },
  "twd": {
    "value": "twd",
    "name": "twd",
    "countries": [
      "tw"
    ]
  },
  "tzs": {
    "value": "tzs",
    "name": "tzs",
    "countries": [
      "tz"
    ]
  },
  "uah": {
    "value": "uah",
    "name": "uah",
    "countries": [
      "ua"
    ]
  },
  "ugx": {
    "value": "ugx",
    "name": "ugx",
    "countries": [
      "ug"
    ]
  },
  "uyu": {
    "value": "uyu",
    "name": "uyu",
    "countries": [
      "uy"
    ]
  },
  "uzs": {
    "value": "uzs",
    "name": "uzs",
    "countries": [
      "uz"
    ]
  },
  "vef": {
    "value": "vef",
    "name": "vef",
    "countries": [
      "ve"
    ]
  },
  "vnd": {
    "value": "vnd",
    "name": "vnd",
    "countries": [
      "vn"
    ]
  },
  "yer": {
    "value": "yer",
    "name": "yer",
    "countries": [
      "ye"
    ]
  },
  "zar": {
    "value": "zar",
    "name": "zar",
    "countries": [
      "za"
    ]
  },
  "zmk": {
    "value": "zmk",
    "name": "zmk",
    "countries": [
      "zm"
    ]
  },
  "zwd": {
    "value": "zwd",
    "name": "zwd",
    "countries": [
      "zw"
    ]
  }
};

  iso.findCountryByCode = function(code) {
    for (var prop in iso.countries) {
      if (iso.countries.hasOwnProperty(prop)) {
        if (iso.countries[prop].alpha2 == code.toLowerCase() || iso.countries[prop].alpha3 == code.toLowerCase()) return iso.countries[prop];
      }
    }
  };

  iso.findCountryByNumber = function(num) {
    num = parseInt(num, 10);
    for (var prop in iso.countries) {
      if (iso.countries.hasOwnProperty(prop)) {
        if (parseInt(iso.countries[prop].number, 10) == num) return iso.countries[prop];
      }
    }
  };

  iso.findCountryByName = function(name) {
    for (var prop in iso.countries) {
      if (iso.countries.hasOwnProperty(prop)) {
        if (iso.countries[prop]['name'] == name.toLowerCase()) return iso.countries[prop];
        else if (iso.countries[prop]['names'] && iso.countries[prop]['names'].indexOf(name.toLowerCase()) > -1) return iso.countries[prop];
      }
    }
  };

  iso.findCountriesByRegion = function(region) {
    var results = [];

    for (var prop in iso.countries) {
      if (iso.countries.hasOwnProperty(prop)) {
        if (iso.countries[prop]['region'] == region) {
          results.push(iso.countries[prop]);
        }
      }
    }
    if (!results.length) return undefined;
    return results;
  };

  iso.getSimpleCountryList = function() {
    var results = [];

    for(var prop in iso.countries) {
      results.push({
        value: iso.countries[prop].value,
        name: iso.countries[prop].name
      });
    }

    return results.sort(function(a,b) {
      if (a.name < b.name)  return -1;
      if (a.name > b.name)  return 1;
      return 0;
    });
  };

  iso.findCurrency = function(currency) {
    for (var prop in iso.currencies) {
      if (iso.currencies.hasOwnProperty(prop)) {
        if (iso.currencies[prop]['value'] == currency) return iso.currencies[prop];
      }
    }
  };

}());