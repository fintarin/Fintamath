#pragma once

namespace fintamath {

class IMathObject;

using ArgumentRef = std::reference_wrapper<const IMathObject>;
using ArgumentPtr = shared_ptr<const IMathObject>;

using ArgumentsRefVector = vector<ArgumentRef>;
using ArgumentsPtrVector = vector<ArgumentPtr>;
using ArgumentsTypesVector = vector<std::reference_wrapper<const std::type_info>>;

}
