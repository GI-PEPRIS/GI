#ifndef ANYWAY_RCF_DIMENSION_STRATEGY_DEFAULT_H
#define ANYWAY_RCF_DIMENSION_STRATEGY_DEFAULT_H


namespace anyway { namespace rcf
{

// This is a strategy placeholder type, which is passed by the algorithm free
// functions to the multi-stage resolving process. It's resolved into an actual
// strategy type during the resolve_strategy stage, possibly depending on the
// input geometry type(s). This typically happens after the resolve_variant
// stage, as it needs to be based on concrete geometry types - as opposed to
// variant geometry types.

struct default_strategy {};

}} // namespace 

#endif