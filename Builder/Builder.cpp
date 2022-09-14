#include <iostream>
#include <vector>

class CPersonLineage
{
    friend class CLineageBuilder;
public:
    std::string GetName() { return fPersonName; }

    void PrintLineage( std::ostream& ost, short generation ) const
    {
        ost << std::string(generation, '\t');
        generation++;
        ost << fPersonName << std::endl;

        for (const auto& child : fLineage)
        {
            child.PrintLineage( ost, generation );
        }
    }

    void AddChild(const std::string& childName)
    {
        fLineage.push_back(CPersonLineage(childName));
    }

    void AddLineage(const CPersonLineage& lineage)
    {
        fLineage.push_back(lineage);
    }
private:
    CPersonLineage(const std::string& name) : fPersonName(name) {}

    std::string fPersonName;
    std::vector<CPersonLineage> fLineage;
};

class CLineageBuilder
{
public:
    static CLineageBuilder Build(const std::string& progenitorName)
    {
        return { progenitorName };
    }

    operator CPersonLineage()
    {
        return fProgenitor;
    }

    void PrintLineage()
    {
        std::ostream& ost = std::cout;

        fProgenitor.PrintLineage(ost, 0);
    }

    CLineageBuilder& AddChild(const std::string& childName)
    {
        fProgenitor.AddChild(childName);
        return *this;
    }

    CLineageBuilder& AddLineage(const CLineageBuilder& builder)
    {
        fProgenitor.AddLineage(builder.fProgenitor);
        return *this;
    }

private:
    CLineageBuilder(const std::string& progenitorName) : fProgenitor(progenitorName) {};

    CPersonLineage fProgenitor;
};

int main()
{
    CLineageBuilder builder = CLineageBuilder::Build("Nikola")
                                .AddLineage(CLineageBuilder::Build("Joro")
                                                .AddChild("Nikola")
                                                .AddChild("Ralica"))
                                .AddLineage(CLineageBuilder::Build("Miro")
                                                .AddChild("Vanesa")
                                                .AddChild("Boyan"));

    builder.PrintLineage();

    CPersonLineage first = builder;
}

