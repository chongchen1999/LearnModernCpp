#include <iostream>
#include <memory>
#include <string>
#include <vector>

int generate_id();

namespace ipr {
// Forward declarations
struct Visitor;
struct Type;
struct Name;
struct Region;

// Basic types that don't need full implementation for this example
struct Annotation {};
struct Unit_location {};
struct Source_location {};
struct Linkage {};

enum Category_code {
    NodeCategory,
    ExprCategory,
    StmtCategory,
    DeclCategory,
    VarCategory
};

// Base class definitions
struct Node {
    const int node_id;
    const Category_code category;
    virtual void accept(Visitor &) const = 0;
    virtual ~Node() = default;

   protected:
    explicit Node(Category_code c) : category(c), node_id(generate_id()) {}
};

struct Expr : Node {
    virtual const Type &type() const = 0;
    ~Expr() override = default;

   protected:
    explicit Expr(Category_code c) : Node(c) {}
};

struct Stmt : Expr {
    virtual const Unit_location &unit_location() const = 0;
    virtual const Source_location &source_location() const = 0;
    virtual const std::vector<Annotation> &annotation() const {
        return annotations;
    }
    ~Stmt() override = default;

   protected:
    explicit Stmt(Category_code c) : Expr(c) {}
    std::vector<Annotation> annotations;
};

struct Decl : Stmt {
    enum Specifier { Static, Extern, Virtual, Public, Private };
    virtual Specifier specifiers() const { return Static; }
    virtual const Linkage &lang_linkage() const { return linkage; }
    virtual const Name &name() const = 0;
    virtual const Region &home_region() const = 0;
    virtual bool has_initializer() const = 0;
    virtual const Expr &initializer() const = 0;
    ~Decl() override = default;

   protected:
    explicit Decl(Category_code c) : Stmt(c) {}
    Linkage linkage;
};

struct Var : Decl {
    ~Var() override = default;

   protected:
    explicit Var(Category_code c) : Decl(c) {}
};

// Basic type implementations
struct Type {
    std::string name;
    explicit Type(std::string n) : name(std::move(n)) {}
};

struct Name {
    std::string identifier;
    explicit Name(std::string id) : identifier(std::move(id)) {}
};

struct Region {
    std::string scope;
    explicit Region(std::string s) : scope(std::move(s)) {}
};

struct Visitor {
    virtual void visit(const Node &) = 0;
    virtual ~Visitor() = default;
};
}  // namespace ipr

// Helper function implementation
int generate_id() {
    static int id = 0;
    return ++id;
}

namespace impl {
template <typename Interface>
struct Node : Interface {
    explicit Node() : Interface(ipr::NodeCategory) {}
    void accept(ipr::Visitor &v) const override { v.visit(*this); }
};

template <typename Interface>
struct Expr : Node<Interface> {
    const ipr::Type *constraint;
    Expr() : Node<Interface>(), constraint(nullptr) {}
    const ipr::Type &type() const override { return *constraint; }
};

template <typename Interface>
struct Stmt : Expr<Interface> {
    ipr::Unit_location unit_locus;
    ipr::Source_location src_locus;
    std::vector<ipr::Annotation> annotations;

    const ipr::Unit_location &unit_location() const override {
        return unit_locus;
    }
    const ipr::Source_location &source_location() const override {
        return src_locus;
    }
    const std::vector<ipr::Annotation> &annotation() const {
        return annotations;
    }
};

template <typename Interface>
struct Decl : Stmt<Interface> {
    const ipr::Name *name_ptr;
    const ipr::Region *home_ptr;
    ipr::Linkage linkage;

    const ipr::Name &name() const override { return *name_ptr; }
    const ipr::Region &home_region() const override { return *home_ptr; }
};

struct Var : Decl<ipr::Var> {
    const ipr::Expr *init;

    Var() : init(nullptr) {
        this->constraint = nullptr;
        this->name_ptr = nullptr;
        this->home_ptr = nullptr;
    }

    bool has_initializer() const override { return init != nullptr; }
    const ipr::Expr &initializer() const override {
        if (!init) throw std::runtime_error("No initializer present");
        return *init;
    }
};
}  // namespace impl

int main() {
    // Create objects for the variable's properties
    auto intType = std::make_unique<ipr::Type>("int");
    auto varName = std::make_unique<ipr::Name>("myVariable");
    auto globalScope = std::make_unique<ipr::Region>("global");

    // Create and populate the variable
    impl::Var variable;
    variable.constraint = intType.get();
    variable.name_ptr = varName.get();
    variable.home_ptr = globalScope.get();

    // Print variable details
    std::cout << "Variable Name: " << variable.name().identifier << '\n';
    std::cout << "Variable Type: " << variable.type().name << '\n';
    std::cout << "Variable Scope: " << variable.home_region().scope << '\n';
    std::cout << "Has Initializer: "
              << (variable.has_initializer() ? "Yes" : "No") << '\n';

    return 0;
}