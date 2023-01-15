#pragma once

#include <iostream>
#include <set>
#include <unordered_map>
#include <queue>

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
		typedef std::pair<unsigned int, int> hyperarc_priority;

		class hyperarc_priority_comparison {
		public:
			bool operator() (const hyperarc_priority& lhs, const hyperarc_priority& rhs) const	{
				return (lhs.first < rhs.first);
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
			hyperarc_set optimal_hyperpath;
			
			std::unordered_map<int, bool> node_reach;
			std::unordered_map<int, size_t> hyperarc_reach;
			std::unordered_map<int, unsigned int> node_dist;
			std::unordered_map<int, unsigned int> hyperarc_dist;
			std::unordered_map<int, int> last_hyperarc;

			// std::priority_queue<hyperarc_priority, std::vector<hyperarc_priority>, hyperarc_priority_comparison>;

			// initialize data structures
			for (int node : this->nodes) {
				node_reach[node] = false;
				node_dist[node] = INT_MAX;
				last_hyperarc[node] = INT_MAX;
			}

			for (const auto& [hyperarc, source_nodes] : this->source_nodes) {
				hyperarc_reach[hyperarc] = source_nodes.size();
				hyperarc_dist[hyperarc] = INT_MAX;
			}

			// TODO: implement Distance and Scan

			// TODO: find optimal hyperpath

			// TODO: zero the weights of the optimal hyperpath arcs

			return optimal_hyperpath;
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