#include <iostream>
#include <vector>

class CPersonLineage
{
public:
    CPersonLineage() = default;
    CPersonLineage(const std::string& name) : fPersonName(name) {}

    std::string GetName() { return fPersonName; }

    std::ostream& PrintLineage()
    {
        std::ostream& ost = std::cout;

        ost << fPersonName << std::endl;

        for (const auto& child : fLineage)
        {
            ost << "\t" << child.fPersonName << std::endl;
        }

        return ost;
    }

    void AddChild(const std::string& childName)
    {
        fLineage.push_back(CPersonLineage(childName));
    }
private:
    std::string fPersonName;
    std::vector<CPersonLineage> fLineage;
};

class CLineageBuilder
{
public:
    CLineageBuilder() = default;
    CLineageBuilder(const std::string& progenatorName) : fProgenitor(progenatorName) {};

    void PrintLineage()
    {
        std::ostream& ost = fProgenitor.PrintLineage();
    }

    void AddChild(const std::string& childName)
    {
        fProgenitor.AddChild(childName);
    }

private:
    CPersonLineage fProgenitor;
};

int main()
{
    CLineageBuilder builder("Nikola");
    builder.AddChild("Joro");
    builder.AddChild("Miro");

    builder.PrintLineage();
}

