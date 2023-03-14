#pragma once

namespace fintamath {

class IMathObject;

using ArgumentsRefVector = vector<std::reference_wrapper<const IMathObject>>;
using ArgumentsPtrVector = vector<shared_ptr<IMathObject>>;
using ArgumentsTypesVector = vector<std::reference_wrapper<const std::type_info>>;

}
