/**
 * @file InterventionComplexity.h
 * @brief Declares the InterventionComplexity enum class representing complexity levels of an intervention.
 */

#pragma once

/**
 * @enum InterventionComplexity
 * @brief Describes the complexity level of an intervention.
 */
enum class InterventionComplexity
{
  EASY,    ///< Basic intervention requiring minimal expertise and time.
  MEDIUM,  ///< Moderate intervention with average technical difficulty.
  HARD,    ///< Complex intervention requiring specialized knowledge.
  EXPERT   ///< Highly complex intervention suitable only for expert technicians.
};