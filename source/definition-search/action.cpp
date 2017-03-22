// Project includes
#include "clang-expand/definition-search/action.hpp"
#include "clang-expand/common/routines.hpp"
#include "clang-expand/definition-search/consumer.hpp"

// LLVM includes
#include <llvm/ADT/StringRef.h>

// Standard includes
#include <string>

namespace ClangExpand {
namespace DefinitionSearch {
Action::Action(const std::string& declarationFile, Query& query)
: _declarationFile(Routines::makeAbsolute(declarationFile)), _query(query) {
}

Action::ASTConsumerPointer Action::CreateASTConsumer(clang::CompilerInstance&,
                                                     llvm::StringRef filename) {
  // Skip the file we found the declaration in
  if (filename == _declarationFile) return nullptr;
  return std::make_unique<Consumer>(_query);
}

}  // namespace DefinitionSearch
}  // namespace ClangExpand
