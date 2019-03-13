#include <cwf/cppwebapplication.h>
#include <cwf/controller.h>
#include <cwf/urlencoder.h>
#include <cwf/sqldatabasestorage.h>
#include <cwf/sqlquery.h>

CWF::SqlDatabaseStorage conexao("QPSQL", "localhost", "postgres", "postgres", "1994", 5432);

class CepController : public CWF::Controller
{
public:
    void doGet(CWF::Request &request, CWF::Response &response) const override
    {
        CWF::SqlQuery query(conexao.getDatabase());
        query.exec("select * from logradouro where logr_cep = '" + request.getParameter("cep") + "'");
        response.write(query.toJson());
    }

    void doPost(CWF::Request &request, CWF::Response &response) const override
    {
        CWF::SqlQuery query(conexao.getDatabase());
        response.write(query.insertFromJson(request.bodyToJsonObject(), "logradouro"));
    }

    void doPut(CWF::Request &request, CWF::Response &response) const override
    {
        CWF::SqlQuery query(conexao.getDatabase());
        response.write(query.updateFromJson(request.bodyToJsonObject(), "logradouro", "logr_cep = '" + request.getParameter("cep") + "'"));
    }

    void doDelete(CWF::Request &request, CWF::Response &response) const override
    {
        CWF::SqlQuery query(conexao.getDatabase());
        response.write(query.deleteRecord("logradouro", "logr_cep = '" + request.getParameter("cep") + "'"));
    }

};


int main(int argc, char *argv[])
{
    CWF::CppWebApplication server(argc, argv, "/home/airton/Documents/CepRest/server");
    server.addController<CepController>("/cep");
    server.start();
}
