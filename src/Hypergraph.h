#pragma once

#include <iostream>
#include <set>
#include <unordered_map>
#include <map>

namespace structHorn {
	
	typedef std::unordered_map<int, std::set<int>> out_hyperarcs_map;
	typedef std::unordered_map<int, std::set<int>> source_nodes_map;
	typedef std::unordered_map<int, int> target_node_map;
	typedef std::unordered_map<int, unsigned int> weight_map;
	typedef std::set<int> node_set;
	typedef std::set<int> hyperarc_set;

	class hypergraph {
	private:
		node_set nodes;
		out_hyperarcs_map out_hyperarcs; // node -> outgoing hyperarcs
		source_nodes_map source_nodes; // hyperarc -> source nodes
		target_node_map target_node; // hyperarc -> target node
		weight_map weight; // hyperarc -> weight

		/*
		enum class node_type {simple, compound};
		typedef std::pair<int, node_type> search_node;
		struct compare_search_nodes {
			bool operator()(const search_node& lhs, const search_node& rhs) {
				return (((lhs.first < rhs.first) && (lhs.second == rhs.second)) || (lhs.second == node_type::simple && rhs.second == node_type::compound));
			}
		};
		*/
	
	public:
		void insert_hyperarc (int hyperarc, node_set source_nodes, int target_node, unsigned int weight) {
			for (int source_node : source_nodes) {
				this->out_hyperarcs[source_node].insert(hyperarc);
				this->nodes.insert(source_node);
			}
			this->nodes.insert(target_node);
			this->source_nodes[hyperarc] = source_nodes;
			this->target_node[hyperarc] = target_node;
			this->weight[hyperarc] = weight;
		}

		hyperarc_set shortest_nontrivial_hyperpath_gt0 (node_set source_nodes, node_set target_nodes) {
			/*
			std::map<search_node, size_t, compare_search_nodes> reach;
			std::map<search_node, unsigned int, compare_search_nodes> dist;
			std::map<search_node, int, compare_search_nodes> last;

			// initialize data structures
			for (int node : this->nodes) {
				search_node snode(node, node_type::simple);
				reach[snode] = 1;
				dist[snode] = INT_MAX;
				last[snode] = INT_MAX;
			}

			for (const auto& [hyperarc, source_nodes] : this->source_nodes) {
				search_node snode(hyperarc, node_type::compound);
				reach[snode] = source_nodes.size();
				dist[snode] = INT_MAX;
			}

			std::cout << "\n";
			for (const auto& [snode, x] : reach) {
				std::cout << "(" << snode.first << ", ";
				if (snode.second == node_type::simple) {
					std::cout << "simple";
				}
				else {
					std::cout << "compund";
				}
				std::cout << ") -> " << x << "\n";
			}
			*/

			// TODO: implement Distance and Scan

			// TODO: find optimal hyperpath

			// TODO: zero the weights of the optimal hyperpath arcs

			// TODO: return optimal hyperpath
		}

		friend std::ostream& operator<<(std::ostream& out, hypergraph& g);
	};

	inline std::ostream& operator<<(std::ostream& out, hypergraph& g) {
		out << "=================================================================\n";
		out << "my hypergraph has " << g.out_hyperarcs.size() << " nodes and " << g.source_nodes.size() << " hyperarcs.\n\n";
		out << "the outgoing hyperarcs of each node:\n";
		for (int node : g.nodes) {
			out << "- node " << node << ":\n";
			for (int hyperarc : g.out_hyperarcs[node]) {
				out << "\t--[" << hyperarc << "]--> " << g.target_node[hyperarc] << "\n";
			}
		}

		out << "\nthe set of hyperarcs:\n";
		for (const auto& [hyperarc, source_nodes] : g.source_nodes) {
			out << "\t{";
			bool first_node = true;
			for (int source_node : source_nodes) {
				if (first_node) {
					first_node = false;
					out << source_node;
				}
				else {
					out << ", " << source_node;
				}
			}
			out << "}\t--[" << hyperarc << "]--> " << g.target_node[hyperarc];
			out << ", w = " << g.weight[hyperarc] << "\n";

		}
		out << "=================================================================\n";
		return out;
	}

}