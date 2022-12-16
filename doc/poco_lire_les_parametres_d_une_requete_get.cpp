//===============================================
// methode 1
//===============================================
// la classe HTMLForm hérite de la classe NameValueCollection,
// qui implémente un itérateur utile pour parcourir les paires "nom=valeur".

string name;
string value;
HTMLForm form( request );

NameValueCollection::ConstIterator i = form.begin();

while(i!=form.end()){

    name=i->first;
    value=i->second;
    cout << name << "=" << value << endl << flush;
    ++i;
}

//===============================================
// methode 2
//===============================================
// En utilisant poco version 1.11.0-all (2021-06-28)

const Poco::URI Uri(request.getURI());
const Poco::URI::QueryParameters QueryParms = Uri.getQueryParameters();

Poco::URI::QueryParameters est:

std::vector<std::pair<std::string, std::string>>

//===============================================
// methode 3
//===============================================
// POCO "NameValueCollection" est presque identique 
// à la classe Vettrasoft Z Directory

using namespace std;

int i, ie;
namevalue_set_o nv;
string_o s = "FOO=BAR;DATE=\"12/21/2012\";HOST=vertigo;OSTYPE=\"Windows Vista\"";
nv.load_from_string(s);
i = 0;

while (i < nv.size())
{
  const namevalue_pair_o &item = nv.get(i, &ie);
  if (!ie)
    cout << item.name() << "=" item.value() << endl << flush;
  ++i;
}

